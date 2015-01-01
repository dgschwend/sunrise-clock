///
/// @mainpage	SunriseClock
/// @details	SunriseClock Software
///
/// @file		SunriseClock.cpp
/// @brief		Main sketch
///
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		David Gschwend
/// @date		28.08.14 20:19
///
/// @copyright	(c) David Gschwend, 2014
/// @copyright	All rights reserved
/// @n
///

/**
 *                       (to FTDI)
 *                      D T R V G G
 *                      |         |
 *                   +---------------+
 *                   |  o o o o o o  |
 *                   | o RAW    TX o |
 *                   | o GND    RX o |
 *                   | o RST   RST o |
 *          +5V      | o VCC*  GND o |    GND
 *                   | o A3 *    2 o |    IR Receiver (IRQ INT0)
 *                   | o A2      3 o |    Light (PWM)
 *                   | o A1      4 o |    LCD SDIN (violet)
 *                   | o A0      5 o |    LCD SCLK
 *  (onboard LED)    | o 13 *    6 o |    LCD SCE  (blue)
 *  Volume load      | o 12 *    7 o |    MP3 Power
 *  Volume clk       | o 11      8 o |    Sound Source Relay
 *  Volume din       | o 10      9 o |    Amplifier Mute
 *                   +---------------+
 *
 *                         * (A4) SDA     RTC I2C Data
 *                         * (A5) SCL     RTC I2C Clock
 *                         * (A6) ADC6    LUX Monitor
 *                         * (A7) ADC7    RTC I2C Clock
 **/

// Include core libraries
#include "Cosa/Board.hh"
#include "Cosa/Board/Arduino/Pro_Mini.hh"
#include "Cosa/OutputPin.hh"
#include "Cosa/AnalogPin.hh"
#include "Cosa/Watchdog.hh"
#include "Cosa/Event.hh"

#include "Cosa/RTC.hh"
#include "Cosa/Power.hh"
#include "Cosa/Watchdog.hh"
#include "Cosa/InputPin.hh"
#include "Cosa/IOStream/Driver/UART.hh"
#include "Cosa/TWI/Driver/DS1307.hh"

#include "StateController.h"
#include "SystemStates.h"
#include "SoundController.h"
#include "MAX7221.h"
#include "LuxMonitor.h"
#include "IRMonitor.h"
#include "TimeKeeper.h"
#include "MP3Controller.h"
#include "TouchMonitor.h"

StateController system(&i_StartupState);

/// @brief  Initialize Sound Controller
/// din      LM1972 Data IN         D10
/// clk      LM1972 Clock signal    D11
/// load     LM1972 Load signal     D12
/// mute     PAM8403 Mute signal    D9
/// relay    Source Switch Relay    D8
/// mp3power MP3 Player Power FET   D7
//
SoundController sound_ctrl(Board::D10, Board::D11, Board::D12, Board::D9, Board::D8, Board::D7);

/// @brief  Initialize Light Controller Driver
/// @param  ledPin  Pin to LED control FET  PWM0 = D3
///
LightController  light_ctrl(Board::PWM0);

// MAX7221 LED Display on Pins  D4-D6
// sdin screen data pin         D4 (violet)
// sclk screen clock pin        D5
// sce  screen chip enable pin  D6 (blue)
LCD::Serial3W   lcd_io(Board::D4, Board::D5, Board::D6);
MAX7221         lcd_ctrl(&lcd_io);
IOStream        lcd(&lcd_ctrl);

// OPT101 Photodiode (blue) on Pin A0
// Change brightness by (new-old)/filterTau every 128ms
LuxMonitor lux_monitor(Board::A0, &lcd_ctrl, 4);

// IR Receiver (green) on Pin D2 (EXT0)
// Monitor IR receiver for 32bit packets, with threshold of 1500us
IRMonitor  ir_monitor(Board::EXT0, &system, 48, 1500);

// DS1307 Real-Time Clock
// Attached to I2C bus, Pins A4 (SDA) & A5 (SCL)
TimeKeeper time_keeper;

// Capacitive Touch Pins
// Connect Pin to Copper Pad and to VCC by 1 MOhm resistor.
// touchLightUp    "Light +" Button   D14
// touchLightDown  "Light -" Button   D15
// touchVolumeUp   "Volume +" Button  D16
// touchVolumeDown "Volume -" Button  D17
//TouchMonitor touch_monitor(Board::D14, Board::D15, Board::D16, Board::D17);

OutputPin led(Board::LED, 0);

IOStream cout(&uart);

void uart_welcome_message();

void setup()
{
    
    RTC::begin();
    Watchdog::begin(16, Watchdog::push_timeout_events);
    
    uart.begin(9600);
    cout << PSTR("UART started") << endl;

    trace.begin(&uart);
    cout << PSTR("Trace started") << endl;

    sound_ctrl.setVolume(0);
    sound_ctrl.stopMP3();
    cout << PSTR("Sound Control started") << endl;
    
    lcd_ctrl.begin();
    cout << PSTR("LCD started") << endl;

    lux_monitor.begin();
    cout << PSTR("Lux Monitor started") << endl;
    
    ir_monitor.reset();
    cout << PSTR("IR Monitor reset and ready.") << endl;
    
    cout << PSTR("TimeKeeper started.") << endl;
    
    light_ctrl.setLevel(255);
    delay(1000);
    light_ctrl.setLevel(0);
    cout << PSTR("LightController started.") << endl;
    
    system.begin();
    cout << PSTR("StateController begin") << endl;
    
    uart_welcome_message();
    cout << PSTR("System Ready!") << endl;
}

void loop()
{
    // Wait for events (low power mode)
    Event event;
    Event::queue.await(&event);
    event.dispatch();
    
    //led.toggle();
    
    // Handle UART Keyboard Input
    if (uart.available()) {
        char c = uart.getchar();
        if (c == 13)  // Enter / PLAY
            system.onIRMessage(SystemState::PLAY);
        if (c == 'w') // UP
            system.onIRMessage(SystemState::UP);
        if (c == 's') // DOWN
            system.onIRMessage(SystemState::DOWN);
        if (c == 'a') // LEFT
            system.onIRMessage(SystemState::LEFT);
        if (c == 'd') // RIGHT
            system.onIRMessage(SystemState::RIGHT);
        if (c == 'm') // MENU
            system.onIRMessage(SystemState::MENU);
        
        if (c == 't') // Test Alarm
            system.change_state(&i_AlarmState);
    }
  
}

void uart_welcome_message() {
    cout << PSTR("            .-'`'-.") << endl;
    cout << PSTR("  ,-'`'.   '._     \\") << endl;
    cout << PSTR(" /    .'  ___ `-._  dg|") << endl;
    cout << PSTR("|   .' ,-' __ `'/.`.'") << endl;
    cout << PSTR("\\ .' \\',-' 12 '-.  '.") << endl;
    cout << PSTR(" ` / / 11    7 1 `.  `.") << endl;
    cout << PSTR("  . '10     /    2 \\  ;") << endl;
    cout << PSTR("  | |      O      3|  |") << endl;
    cout << PSTR("  | |9      \\      '  '") << endl;
    cout << PSTR("  '  \\ 8     \\   4/  /") << endl;
    cout << PSTR("   '. `'.7  6  5.'  '") << endl;
    cout << PSTR("     `. _ `'''` _.'\\\\-.") << endl;
    cout << PSTR("      .//`''--''   (   )") << endl;
    cout << PSTR("     (   )          '-`") << endl;
    cout << PSTR("      `-'  ~ SunRiseClock ~") << endl << endl;
}
