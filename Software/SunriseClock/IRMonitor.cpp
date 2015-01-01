///
/// @file		IRMonitor.cpp
/// @n
/// @n @b		Project SunriseClock
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		David Gschwend
///
/// @date		02.09.14 17:19
/// @copyright	(c) David Gschwend, 2014
///

// Core library - IDE-based
#if defined(COSA)
#else // error
#error Platform not defined
#endif // end IDE

#include "IRMonitor.h"
#include "Cosa/Trace.hh"

extern IOStream cout;

///@n Keymap for Apple Remote (bits=32)
//const IRMonitor::keymap_t IRMonitor::m_keymap[] = {
//    { 0xb90a87ee, SystemState::UP   },
//    { 0xb90c87ee, SystemState::DOWN  },
//    { 0xb90987ee, SystemState::LEFT  },
//    { 0xb90687ee, SystemState::RIGHT },
//    { 0xb90587ee, SystemState::PLAY  },
//    { 0xb90387ee, SystemState::MENU  },
//    { 0xFFFFFFFE, SystemState::REPEAT}
//};

//@n Keymap for DENON Remote (bits=48)
const IRMonitor::keymap_t IRMonitor::m_keymap[] = {
    { 0x13420150, SystemState::UP   },
    { 0x03421150, SystemState::DOWN  },
    { 0x33422150, SystemState::LEFT  },
    { 0x23423150, SystemState::RIGHT },
    { 0x53424150, SystemState::PLAY  },
    { 0x15440150, SystemState::MENU  },
    { 0xFFFFFFFE, SystemState::REPEAT}
};

/////@n Dummy Keymap for no known Remote
//const IRMonitor::keymap_t IRMonitor::m_keymap[] = {
//    // X1503254c8d0
//    { 0x01, SystemState::UP   },
//    { 0x02, SystemState::DOWN  },
//    { 0x03, SystemState::LEFT  },
//    { 0x04, SystemState::RIGHT },
//    { 0x05, SystemState::PLAY  },
//    { 0x06, SystemState::MENU  },
//    { 0xFFFFFFFE, SystemState::REPEAT}
//};

const uint8_t IRMonitor::m_keys = membersof(IRMonitor::m_keymap);

void
IRMonitor::on_interrupt(uint16_t arg)
{
    UNUSED(arg);
    
    // Check if the buffer is full
    if (m_ix == m_max) { return; }
    
    // Check if the time should be set; i.e. queue for timeout events
    if (m_ix == 0) { detach(); Watchdog::attach(this, TIMEOUT); }
    
    // Measure the sample period
    uint32_t stop = RTC::micros();
    uint32_t us = (stop - m_start);
    m_start = stop;
    
    // Detect Repeat Code
    if (m_ix < 2 && (us > 10000 && us < 12000)) {
        // REPEAT CODE detected, send event, will soon reset.
        Event::push(Event::READ_COMPLETED_TYPE, this, SystemState::REPEAT);
        return;
    }
    
//    // Detect leader sequence: REMARK: Not necessary, m_ix always reported as 1.
//    if (m_ix < 4 && (us > 12500 && us < 14500)) {
//        // LEADER SEQUENCE detected, re-align.
//        //m_samples[0] = 999;
//        cout << PSTR("realign at m_ix=") << m_ix << endl;
//        m_ix = 1;
//    }
    
    m_samples[m_ix] = us;
    
    // Generate binary code. Skip two first and two last samples (=first repeat code)
    if (m_ix > 1 && m_ix < m_max)
        m_code = (m_code >> 1) | ((uint32_t)(us > m_threshold) << 31);
    
    // Check if all samples have been received
    if (++m_ix != m_max) return;
    
    // Disable further interrupts and remove from timer queue
    disable();
    detach();
    
    // DEBUG:
//    cout << PSTR("\r\n") << bin << m_code << PSTR("\r\n");
//    cout << PSTR("\r\n") << hex << m_code << PSTR("\r\n");
//    while (m_ix>0) {
//        cout << PSTR("\r\nsample") << m_ix << PSTR(": ") << m_samples[m_ix--] << PSTR("\r\n");
//    }
    
    // Push an event with the received code
    Event::push(Event::READ_COMPLETED_TYPE, this, lookup(m_code));
}

void
IRMonitor::reset()
{
    // Remove from any queue
    detach();
    
//    // Reset Samples Array
//    for (uint8_t i = 0; i<=m_ix; i++) {
//        m_samples[i] = 0;
//    }
    
    // Initial state
    m_ix = 0;
    m_code = 0;
    
    // Reset start time and enable the interrupt handler
    m_start = RTC::micros();
    enable();
}

// Lookup Code. Send latest code again in case of REPEAT.
SystemState::IRMessage
IRMonitor::lookup(uint32_t code)
{
    // save last message, so we can send it again upon REPEAT.
    //static SystemState::IRMessage last_msg = SystemState::ILLEGAL;
    //SystemState::IRMessage current_msg;
    
    for (uint8_t i = 0; i < m_keys; i++)
        if (code == m_keymap[i].code) {
            //current_msg = m_keymap[i].msg;
            //if (current_msg == SystemState::REPEAT)
                //current_msg = last_msg; // overwrite current msg with last one
            //else
                //last_msg = current_msg; // save current msg for next call
            //return current_msg;
            return m_keymap[i].msg;
        }
    
    // WARNING: Enabling Trace in Interrupt will cause intermittent freezes!
    // trace << PSTR("Error: Unknown IR code ") << hex << code << endl;
    
    return SystemState::ILLEGAL;
}

void
IRMonitor::on_event(uint8_t type, uint16_t value) {
    
    //trace << endl << PSTR("EVENT") << endl;

    if (type == Event::TIMEOUT_TYPE) {
//        trace << PSTR("[");
//        for (uint8_t i = 0; i<38; i++) {
//            trace << (m_samples[i]>>8) << PSTR(" ");
//        } trace << PSTR("0];") << endl;
//        trace << PSTR(" - - -- TIMEOUT HAPPENED IN IR_MONITOR!!") << endl;
//        trace << PSTR("Timeout. m_ix was ") << m_ix << endl;
//        trace << PSTR("Time since start of IR Message: ") << (RTC::micros()-m_start) << endl;

        reset();
        return;
        
    }
    if (type == Event::READ_COMPLETED_TYPE) {
        
//        trace << PSTR("* [");
//        for (uint8_t i = 0; i<38; i++) {
//            trace << (m_samples[i]) << PSTR(" ");
//        }
//        trace << PSTR("0];") << endl;
//        trace << PSTR(" - - -- READ_COMPLETE HAPPENED IN IR_MONITOR!!") << endl;
//
        //TRACE(m_samples[0]);
        
        reset();
        
        // WORKAROUND: HANDLE DOUBLE-MESSAGES SENT BY DENON REMOTE
        static bool second = false;
        cout << PSTR("WARNING: DENON REMOTE UN-DOUBLING IN EFFECT (IRMonitor.cpp)") << endl;
        if (second) {second = false;} else {second = true; return;}
        // END WORKAROUND

        m_system_controller->onIRMessage((SystemState::IRMessage) value);
        
        return;
    }
}
