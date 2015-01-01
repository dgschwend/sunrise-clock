///
/// @file		MP3Controller.h
/// @n
/// @n @b		Project SunriseClock
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		David Gschwend
///
/// @date		02.09.14 17:19
/// @copyright	(c) David Gschwend, 2014
///

/**
 * Device Driver for MPMan MP3 Controller
 * (controlled by simulating button presses)
 *
 * Connect wires from the active end of the necessary buttons
 * directly to our Arduino. So we can pull them to GND to simulate
 * a button pressed.
 *
 * @section Circuit
 * @code
 *
 *                   ||--- (VCC)
 * (powerPin)--------||
 *                   ||------+
 * (GND)------------------+  |
 *                       _v__v_
 *                      |      |
 *                   ___|______|___
 * (playPin)-------C| PLAY  ____   |
 *                  |      |    |  |
 * (backPin)-------C| BACK |    |  |
 *                  |      |    |  |
 *                 C|      |    |  |
 *                  |      |    |  |
 * (modePin)-------C| MENU |    |  |
 *                  |      |____|  |
 *                 C| REC          |
 *                  |              |
 *                 C|              |
 *                  |              |
 *                 C|        MPMan |
 *                  |______________|
 * @endcode
 **/

// Core library - IDE-based
#if defined(COSA)
#else // error
#error Platform not defined
#endif // end IDE

#include "Cosa/Board.hh"
#include "Cosa/OutputPin.hh"
#include "Cosa/PWMPin.hh"
#include "Cosa/Types.h"

#ifndef MP3Controller_h
#define MP3Controller_h

/// @brief MP3Contorller Class
/// @brief Controls an old MPMan MP3 Player by simulating button presses
class MP3Controller {
public:
   
    /// @brief  Constructor: Initialize new duty-cycled LED
    /// @details: PWM0 = D3, PWM1 = D5, PWM2 = D6, PWM3 = D9, PWM4 = D10, PWM5 = D11
    MP3Controller(Board::DigitalPin playPin, Board::DigitalPin backPin, Board::DigitalPin modePin, Board::DigitalPin powerPin, Board::DigitalPin powerPin2, Board::DigitalPin relayPin) : m_play(playPin, 1), m_back(backPin, 1), m_mode(modePin, 1), m_power(powerPin, 0), m_power2(powerPin, 0), m_relay(relayPin, 0)
    {};
    
    /// @brief Start up and start Playing
    /// @brief BLOCKING CALL, takes around 15s.
    void play();
    
    /// @brief Reset, stop Playing and Shut down
    /// @brief BLOCKING CALL, takes around 14s.
    void stop();
    
    
private:
    OutputPin  m_play, m_back, m_mode, m_power, m_power2, m_relay;
};

#endif
