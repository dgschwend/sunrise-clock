//
// LM1972.cpp
//
// ----------------------------------
// Developed with embedXcode+
// http://embedXcode.weebly.com
//
// Project 		SunriseClock
//
// Created by 	David Gschwend, 21.08.14 20:36
// 				David Gschwend
//
// Copyright 	© David Gschwend, 2014
// License		All rights reserved
//
// See 			SoundController.h for references
//

#include "SoundController.h"

///
/// @brief  Initialize new SoundController connected to given Pins
/// @param  din Pin connected to LM1972 Data IN signal
/// @param	clk Pin connected to LM1972 Clock signal
/// @param	load Pin connected to LM1972 Load signal
/// @param	mute Pin connected to PAM8403 Mute signal
/// @param	relay Pin connected to Sound Source Switch Relay
/// @param	mp3power Pin connected to MP3 Player Power Switch
///
SoundController::SoundController(Board::DigitalPin din, Board::DigitalPin clk,
                                 Board::DigitalPin load, Board::DigitalPin mute,
                                 Board::DigitalPin relay, Board::DigitalPin mp3power):
                lm1972(din, load, clk),
                m_mute(mute, 0),            // active low
                m_mp3power(mp3power, 1),    // active low
                m_relay(relay, 0)           // low = external, high = internal
{};


///
/// @brief  Set sound volume: 0 (mute) to 80 (max).
/// @details    Approximately +1dB per step.
/// @param      volume New volume, between 0 (mute) and 80 (max).
///
void SoundController::setVolume(uint8_t volume) {
    // Calculate necessary LM1972 attenuation value:
    /*
     Data Word | Attenuation Lvl (dB) |   Volume (dB)
     ---------------------------------------------
         0     |          0.0         |     80
         1     |          0.5         |     80
         2     |          1.0         |     79
       ...     |          ...         |    ...
        94     |         47.0         |     33
        95     |         47.5         |     33
        96     |         48.0         |     32
        97     |         49.0         |     31
        98     |         50.0         |     30
       ...     |          ...         |    ...
       125     |         77.0         |      3
       126     |         78.0         |      2
       127     |         79.0         |      1
       128     |        100.0         |      0
     
     value = (volume > 32) ? (80 - volume)*2 : (128 - volume)
     volume = (value > 95) ? (128 - value) : (80 - value/2)
    */
    
    // Amplifier MUTE
    if (volume == 0) {
        m_mute.low();         // Volume = 0: mute (active-low)
    } else {
        m_mute.high();        // Volume > 0: unmute.
    }
    
    // LM1972 Attenuation Setting
    uint8_t value = (volume > 32) ? (80 - volume)*2 : (128 - volume);
    lm1972.setAttenuation(value);
}

///
/// @brief  Get sound volume, between 0 (mute) to 80 (max).
/// @details    Approximately +1dB per step
///
uint8_t SoundController::getVolume() {
    // See ::setVolume() for calculation
    uint8_t value = lm1972.getAttenuation();
    uint8_t decibel = (value > 95) ? (128 - value) : (80 - value/2);
    return decibel;
}

///
/// @brief      Start MP3 Player and switch to internal sound source.
/// @details    Applies power to the MP3 player, switches input relay to "internal" mode.
void SoundController::startMP3() {
    m_mp3power.low();   // power ON (active low)
    m_relay.high();     // source: internal
}

///
/// @brief      Stop MP3 Player and switch to external sound source.
/// @details    Disables power to the MP3 player, switches input relay to "external" mode.
void SoundController::stopMP3() {
    m_mp3power.high();  // power OFF (active low)
    m_relay.low();      // source: external
}

