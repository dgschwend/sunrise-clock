///
/// @file		TouchMonitor.cpp
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

#include "TouchMonitor.h"

extern StateController system;

TouchMonitor::TouchMonitor(Board::DigitalPin touchLightUp, Board::DigitalPin touchLightDown, Board::DigitalPin touchVolumeUp, Board::DigitalPin touchVolumeDown) :
    m_lightUp(touchLightUp, SystemState::LightUp),
    m_lightDown(touchLightDown, SystemState::LightDown),
    m_volumeUp(touchVolumeUp, SystemState::VolumeUp),
    m_volumeDown(touchVolumeDown, SystemState::VolumeDown)
{};

void TouchMonitor::handleTouch(SystemState::BUTTON button_id) {
    system.onTouch(button_id);
}