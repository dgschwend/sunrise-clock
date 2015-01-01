///
/// @file		LuxMonitor.cpp
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

#include "LuxMonitor.h"
#include "Cosa/Trace.hh"

    /// @brief  Constructor:
    /// @param  opt101Pin    Board Pin connected to "OPT101" Output
    /// @param  &lcd_ctrl    Pointer to MAX7221 class for Brightness Control
    /// @param  filterTau    Filter Bandwidth (filterTau * 128ms). Chose power of 2.
LuxMonitor::LuxMonitor(Board::AnalogPin opt101Pin, MAX7221 *lcd_ctrl, uint8_t filterTau=8): Periodic(128), m_filterTau(filterTau), m_lcd_ctrl(lcd_ctrl), m_opt101Pin(opt101Pin), brightness(0) {};


    /// @brief  Method is called periodically (every 128ms)
void LuxMonitor::run() {
    
    // get previously converted brightness value
    uint16_t lightVal = m_opt101Pin.get_value();
    
    // apply low-pass FIR Filter (-3dB bandwidth: m_filterTau*128ms)
    brightness = brightness + ((int16_t)lightVal-(int16_t)brightness)/m_filterTau;
    
    // convert brightness (~0 to 800) to contrast value (0 to 15) and set display brightness.
    uint8_t contrast = brightness/32;
    if (contrast>15) contrast = 15;
    m_lcd_ctrl->display_contrast(contrast);
        
    // request sample in the background --> should be ready on next run().
    m_opt101Pin.sample_request();
    
}
