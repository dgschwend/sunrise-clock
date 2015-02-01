///
/// @file		LuxMonitor.h
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
 * OPT101 Brightness Sensor *
 *
 * @section Circuit
 * @code
 *                    MAX7221/LCD::Serial3W
 *                       +------------+
 *       (+5V)---------1-|VCC      GND|-8----(GND)
 *                   --2-|NC        NC|-7--
 *       (GND)---------3-|V-        NC|-6--
 *                +----4-|FB       OUT|-5---o---> (A0)
 *                |      +------------+     |
 *                +-------------------------+
 * @endcode
 **/



// Core library - IDE-based
#if defined(COSA)
#else // error
#error Platform not defined
#endif // end IDE

#include "Cosa/Board.hh"
#include "Cosa/Periodic.hh"
#include "Cosa/AnalogPin.hh"
#include "MAX7221.h"

#ifndef LuxMonitor_h
#define LuxMonitor_h

/// @brief    Brightness Monitor Class -- automatically adjusts LCD brightness.
/// @details  Works with TI OPT101 Brightness Sensor or similar.
/// @details  Once instantiated and initialized with .begin(), samples every 128ms, lowpasses value and adjusts LED brightness accordingly.
class LuxMonitor : public Periodic {
    
public:
   
    /// @brief  Constructor:
    /// @param  opt101Pin    Board Pin connected to "OPT101" Output
    /// @param  *lcd_ctrl    Pointer to MAX7221 instance for Brightness Control
    /// @param  filterTau    Parameter for adjusting smoothing/lowpass (128ms period, each add (diff/tau))
    LuxMonitor(Board::AnalogPin opt101Pin, MAX7221 *lcd_ctrl, uint8_t filterTau);
    
    /// @brief  Method is called periodically
    virtual void run();
    
    // memory for filtered brightness from sensor (~0 to 800)
    uint16_t brightness;
    
private:
    const uint8_t   m_filterTau;
    MAX7221         *m_lcd_ctrl;
    AnalogPin       m_opt101Pin;
};

#endif
