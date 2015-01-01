///
/// @file		MP3Controller.cpp
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

#include "MP3Controller.h"
#include "Cosa/Trace.hh"

void MP3Controller::play() {
    
    // Default Control Pins to High.
    m_play.high();
    m_back.high();
    m_mode.high();
    
    // Turn on Power, wait for stabilization
    trace << PSTR("Turn on Power...") << endl;
    m_power.on();
    m_power2.on();
    sleep(2);
    
    // Press Play to Wake up Player
    trace << PSTR("Turn on Player...") << endl;
    m_play.low();
    sleep(1);
    m_play.high();
    
    // Wait for startup
    trace << PSTR("Wait for startup") << endl;
    sleep(8);
    
    // Homing Sequence
    trace << PSTR("Return to Home Menu") << endl;
    m_mode.low();
    sleep(2);
    m_mode.high();

    trace << PSTR("Load Home Menu...") << endl;
    sleep(1);

    trace << PSTR("Enter Music Mode") << endl;
    m_mode.low();
    delay(100);
    m_mode.high();
    
    // Wait for mode switch
    trace << PSTR("Wait for Switching") << endl;
    delay(5000);
    
    // Switch Audio Source to MP3 Player
    trace << PSTR("Switch Audio Out to MP3") << endl;
    m_relay.on();
    
    // Play
    trace << PSTR("Play") << endl;
    m_play.low();
    delay(100);
    m_play.high();
    
    delay(1000);
    trace << PSTR("Now playing...") << endl;
    
}


void MP3Controller::stop() {
    
    // Switch Audio Source to External Input
    trace << PSTR("Switch Audio Out to External") << endl;
    m_relay.off();
    
    // Go back
    trace << PSTR("Pause Song..") << endl;
    m_play.low();
    delay(100);
    m_play.high();
    
    trace << PSTR("Waiting...") << endl;
    delay(4000);
    
    // Go one song back
    trace << PSTR("One Song Back.") << endl;
    m_back.low();
    delay(200);
    m_back.high();
    
    trace << PSTR("Waiting (Checking License)...") << endl;
    delay(4400);
    
    // Turn off
    trace << PSTR("Turn off") << endl;
    m_play.low();
    delay(1000);
    m_play.high();
    delay(3000);
    
    // Switch off Power, Comm Pins low to prevent backfeeding
    trace << PSTR("Switch Power off") << endl;
    m_power.off();
    m_power2.off();
    m_play.low();
    m_back.low();
    m_mode.low();
    delay(1000);
    
}