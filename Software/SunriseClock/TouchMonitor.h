///
/// @file		TouchMonitor.h
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
#include "Cosa/Periodic.hh"
#include "Cosa/Touch.hh"
#include "StateController.h"

#ifndef TouchMonitor_h
#define TouchMonitor_h

/// @brief  Touch Monitor Class
class TouchMonitor {
    
public:
    
    /// @brief  Constructor:
    /// @param  touchLightUp    Board Pin connected to "Light +" Button
    /// @param  touchLightDown  Board Pin connected to "Light -" Button
    /// @param  touchVolumeUp   Board Pin connected to "Volume +" Button
    /// @param  touchVolumeDown Board Pin connected to "Volume -" Button
    TouchMonitor(Board::DigitalPin touchLightUp, Board::DigitalPin touchLightDown, Board::DigitalPin touchVolumeUp, Board::DigitalPin touchVolumeDown);

private:
    
    /// @brief  Class Implements one Cosa-Touch Button. On touch, calls the TouchMonitor handleTouch() method with it's ID.
    class TouchKey : private Touch {
    private:
        SystemState::BUTTON m_ButtonID;
        void on_touch() { TouchMonitor::handleTouch(m_ButtonID); }
    public:
        TouchKey(Board::DigitalPin pin, SystemState::BUTTON id):
            Touch(pin), m_ButtonID(id) {};
    };
    
    TouchKey m_lightUp, m_lightDown, m_volumeUp, m_volumeDown;
        
    /// @brief  Method is called whenever a button is touched.
    static void handleTouch(SystemState::BUTTON button_id);
};

#endif
