///
/// @file		IRMonitor.h
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

#include "Cosa/Board.hh"
#include "Cosa/ExternalInterrupt.hh"
#include "Cosa/Linkage.hh"
#include "Cosa/Event.hh"
#include "StateController.h"

#ifndef IRMonitor_h
#define IRMonitor_h


/// @brief    Infrared Receiver Monitor Class -- fetches, interprets and relays messages to SystemController.
/// @details  Works with TSOP4838 and similar Infrared Receivers.
/// @details  Once instantiated and initialized with .begin(), receives on Interrupt.
/// @details  --> mostly copied from Cosa IR::Receiver.
class IRMonitor : private ExternalInterrupt, private Link {
public:
    
    /**
     * Mapping structure from code to key. Data structure
     * for storage in program memory.
     */
    struct keymap_t {
        uint32_t code;
        SystemState::IRMessage msg;
    };
    typedef const keymap_t* keymap_P;
    
    /**
     * @override Interrupt::Handler
     * Interrupt pin handler: Measure time periods of pulses in sequence
     * from IR receiver circuit. Call handle_message(code) when a full
     * sequence has been recieved; where code is the recieved binary code.
     * @param[in] arg argument from interrupt service routine.
     */
    virtual void on_interrupt(uint16_t arg = 0);
    
    /**
     * Construct an IRMonitor connected to the given interrupt pin,
     * capture given max number of samples, and decode to binary
     * with the given threshold.
     * @param[in] pin interrupt pin (Board::EXTn).
     * @param[in] max number of samples.
     * @param[in] threshold level for mapping to binary.
     */
    IRMonitor(Board::ExternalInterruptPin pin, StateController *system,
             uint8_t bits = 32, uint32_t threshold = 1600) :
    ExternalInterrupt(pin, ExternalInterrupt::ON_FALLING_MODE),
    Link(),
    m_threshold(threshold),
    m_start(0),
    m_code(0),
    m_ix(0),
    m_max(bits+2),
    m_system_controller(system) {
        disable();  // disable interrupt until first "reset".
    }
    
    /**
     * Reset the receiver for the next code sequence.
     */
public:
    void reset();
    
    /**
     * Lookup given code and return key or EOF(-1).
     * @param[in] code to lookup in key map.
     * @return key or EOF(-1).
     */
    SystemState::IRMessage lookup(uint32_t code);

private:
    virtual void on_event(uint8_t type, uint16_t value);
    
private:
    StateController* m_system_controller;
    static const uint16_t TIMEOUT = 512;
    volatile uint32_t m_threshold;
    volatile uint32_t m_start;
    volatile uint32_t m_code;
    volatile uint8_t m_ix;
    const uint8_t m_max;
    static const keymap_t m_keymap[];
    static const uint8_t m_keys;
public:
    volatile uint16_t m_samples[100];
};

#endif
