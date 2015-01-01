///
/// @file		LM1972.h
/// @brief		Library header
///
/// @details	Device Driver for Communication with Audio Attenuation IC LM1972
/// @n
/// @n @b		Project LM1972_Driver
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		David Gschwend
///
/// @date		21.08.14 20:36
///
/// @copyright	(c) David Gschwend, 2014
/// @copyright	All rights reserved
///
///

// Core library for code-sense
#if defined(COSA) // Cosa specific
#else
#error Platform not defined
#endif

#ifndef LM1972_Driver_h
#define LM1972_Driver_h

// Include core libraries
#include "Cosa/OutputPin.hh"
#include "Cosa/Types.h"
#include "Cosa/Trace.hh"

/**
 * @brief	Device Driver for LM1972 Audio Attenuation IC
 * @details Datasheet: http://www.ti.com/lit/ds/symlink/lm1972.pdf

 * @section Circuit
 * @code
 *                 _________________
 *                |                 |
 *           |--- | GND AC      IN2 | -------- RIGHT IN
 *  OUT LEFT ---- | OUT1       GND2 | ----|
 *           |--- | GND        VSS1 | ----|
 *  IN LEFT ----- | IN1        OUT2 | -------- RIGHT OUT2
 *           |--- | GND AC   GND AC | ----|
 *           |--- | GND AC     VDD2 | -------^ (+12V)
 *           |--- | VSS2     GND AC | ----|
 *  (GND) ------- | DGND       VDD1 | -------^ (+12V)
 *  (clk) ------- | CLK        DOUT | --------_
 *  (load) ------ | LOAD        DIN | --+    | | R
 *                |_________________|   |    | | 2k
 *  (din) ------------------------------+     ¨-----|
 *
 * @endcode
 **/

class LM1972 {
    
public:
    ///
    /// @brief  Initialize new LM1972 Driver connected to given Pins
    /// @param  din Pin connected to LM1972 Data IN signal
    /// @param	clk Pin connected to LM1972 Clock signal
    /// @param	load Pin connected to LM1972 Load signal
    ///
    LM1972(Board::DigitalPin din, Board::DigitalPin clk, Board::DigitalPin load);
    
    ///
    /// @brief  Set attenuation value in LM1972 (and update this class' shadow copy of attenuation value)
    /// @details    Values between 0 and 96 result in -0.5dB attenuation steps (-0dB to -48dB). Values between 96 and 126 result in -1dB attenuation steps (-48dB to -78dB). Values >= 127 result in Muting Function / attenuation of -79dB (actual attenuation is even higher, about -104dB).
    /// @param      attenuation New attenuation value.
    ///
    void setAttenuation(uint8_t attenuation);
    
    ///
    /// @brief  Set attenuation value in Decibel (and update this class' shadow copy of attenuation value)
    /// @param      attenuation New attenuation value in Decibel. Possible values range from -0dB to -78dB. Attenuations greater than -78dB result in Mute function (approx. -104dB).
    ///
    void setAttenuationDB(uint8_t decibel);
    
    ///
    /// @brief  Get current attenuation value in steps (shadowed in this class, because LM1972 value is write-only)
    /// @details    Values between 0 and 96 represent -0.5dB attenuation steps (-0dB to -48dB). Values between 96 and 126 represent -1dB attenuation steps (-48dB to -78dB). Values >= 127 result in Muting Function / attenuation of -79dB (actual attenuation is even higher, around -104dB).
    ///
    uint8_t getAttenuation();
    
    ///
    /// @brief  Get current attenuation value in Decibel (shadowed in this class, because LM1972 value is write-only)
    /// @details    Returns value between 0 and 79, representing the current attenuation level in Decibel.
    ///
    uint8_t getAttenuationDB();
    
    enum ADDRESS {
        channel1 = 0x00,
        channel2 = 0x01,
        channel3 = 0x02 };
    
private:
    
    uint8_t m_attenuation;
    
    OutputPin m_din;
    OutputPin m_clk;
    OutputPin m_load;
    
    void set(LM1972::ADDRESS addr, uint8_t data);
    
};

#endif
