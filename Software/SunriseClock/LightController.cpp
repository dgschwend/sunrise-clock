///
/// @file		LightController.cpp
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

#include "LightController.h"
#include "Cosa/Trace.hh"

/// @brief Set a new light Level (starts transition)
void LightController::setLevel(uint8_t newLevel) {
    level = newLevel;
    //m_ledPin.set(newLevel);
    Periodic::begin();
}

/// @brief Set a new light Level immediately
void LightController::setLevelImmediately(uint8_t newLevel) {
    level = newLevel;
    m_ledPin.set(newLevel);
}

/// @brief Get currently set light Level
uint8_t LightController::getLevel() {
    return level;
};

///@brief Periodically called function (every 16ms = 64 fps, 2s for full ramp)
void LightController::run() {
        
    if (curr_level < level) curr_level++;       // Change current level
    else if (curr_level > level) curr_level--;
    
    if (curr_level < level) curr_level++;       // Apply twice for speedup
    else if (curr_level > level) curr_level--;
    
    m_ledPin.set(pgm_read_byte_near(LED_LINEARIZE + curr_level));
    
    if (curr_level == level) {
        Periodic::end();
    }

};