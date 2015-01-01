//
// LM1972.cpp
//
// ----------------------------------
// Developed with embedXcode+
// http://embedXcode.weebly.com
//
// Project 		LM1972_Driver
//
// Created by 	David Gschwend, 21.08.14 20:36
// 				David Gschwend
//
// Copyright 	© David Gschwend, 2014
// License		All rights reserved
//
// See 			LM1972.h for references
//

#include "LM1972.h"

LM1972::LM1972(Board::DigitalPin din, Board::DigitalPin clk, Board::DigitalPin load): m_attenuation(128), m_din(din), m_clk(clk), m_load(load) {};

void LM1972::setAttenuationDB(uint8_t decibel) {
    // Default: Mute, actually -104dB, displayed as -79dB.
    uint8_t attenuation = 128;
    
    // -48dB to -78dB: 1dB per step.
    if (decibel >= 48 && decibel <= 78) {
        // Attenuation levels 96 to 126
        attenuation = (decibel - 48) + 96;
    }
    
    // -0dB to -48dB: 0.5dB per step.
    if (decibel < 48) {
        // Attenuation levels 0 to 96
        attenuation = (decibel * 2);
    }
    
    this->setAttenuation(attenuation);
}

void LM1972::setAttenuation(uint8_t attenuation) {
    this->set(channel1, attenuation);
    this->set(channel2, attenuation);
    this->set(channel3, attenuation);
    this->m_attenuation = attenuation;
}

uint8_t LM1972::getAttenuation() {
    return this->m_attenuation;
}

uint8_t LM1972::getAttenuationDB() {
    
    // Get shadowed attenuation.
    uint8_t attenuation = this->getAttenuation();
    
    // Default: Mute, -79dB (actually even -104dB).
    uint8_t decibel = 79;
    
    // Attenuation levels 96 to 126: 1dB per step.
    if (attenuation >= 96 && attenuation <= 126) {
        // -48dB to -78dB
        decibel = (attenuation - 96) + 48;
    }
    
    // Attenuation levels 0 to 96: 0.5dB per step.
    if (attenuation < 96) {
        // -0dB to -48dB
        decibel = (attenuation / 2);
    }
    
    return decibel;
}

void LM1972::set(LM1972::ADDRESS addr, uint8_t data) {
    
    m_load.low();
    m_clk.off();
    DELAY(1);
    
    for (uint8_t i = 0; i < 8; i++) {
        m_din << (addr & (1 << (7-i)));
        DELAY(1);
        m_clk.on();
        DELAY(1);
        m_clk.off();
    }
    
    for (uint8_t i = 0; i < 8; i++) {
        m_din << (data & (1 << (7-i)));
        DELAY(1);
        m_clk.on();
        DELAY(1);
        m_clk.off();
    }
    
    //m_din.write((uint8_t) addr, m_clk);
    //m_din.write((uint8_t) data, m_clk);
    
    DELAY(1);
    m_load.high();
    m_clk.off();
    m_din.off();
    
}