///
/// @file		SoundController.h
/// @brief		Sound Controller Library
///
/// @details	Driver for MP3, Sound Switch and Volume Control
/// @n
/// @n @b		Project SunriseClock
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

#ifndef SOUND_CONTROLLER_h
#define SOUND_CONTROLLER_h

// Include core libraries
#include "LM1972.h"
#include "Cosa/Types.h"

/**
 * @brief	Sound Controller for starting Sound, Switching Source, setting Volume
 **/

class SoundController {
    
public:
    ///
    /// @brief  Initialize new SoundController connected to given Pins
    /// @param  din Pin connected to LM1972 Data IN signal
    /// @param	clk Pin connected to LM1972 Clock signal
    /// @param	load Pin connected to LM1972 Load signal
    /// @param	mute Pin connected to PAM8403 Mute signal
    /// @param	relay Pin connected to Sound Source Switch Relay
    /// @param	mp3power Pin connected to MP3 Player Power Switch
    ///
    SoundController(Board::DigitalPin din, Board::DigitalPin clk, Board::DigitalPin load, Board::DigitalPin mute, Board::DigitalPin relay, Board::DigitalPin mp3power);
    
    ///
    /// @brief  Set sound volume: 0 (mute) to 80 (max).
    /// @details    Approximately +1dB per step.
    /// @param      volume New volume, between 0 (mute) and 80 (max).
    ///
    void setVolume(uint8_t volume);
    
    ///
    /// @brief  Get sound volume, between 0 (mute) to 80 (max).
    /// @details    Approximately +1dB per step.
    ///
    uint8_t getVolume();

    ///
    /// @brief      Start MP3 Player and switch to internal sound source.
    /// @details    Applies power to the MP3 player, switches input relay to "internal" mode.
    void startMP3();
    
    ///
    /// @brief      Stop MP3 Player and switch to external sound source.
    /// @details    Disables power to the MP3 player, switches input relay to "external" mode.
    void stopMP3();
    
private:
    
    OutputPin m_mute;
    OutputPin m_relay;
    OutputPin m_mp3power;
    
    LM1972 lm1972;
    
};

#endif
