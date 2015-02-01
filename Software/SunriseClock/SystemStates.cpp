///
/// @file		SystemStates.cpp
/// @brief		Actual System State Implementations
/// @details	Models a certain state in the System State Machine.
/// @n
/// @n @b		Project SunriseClock
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		David Gschwend
/// @author		David Gschwend
///
/// @date		02.09.14 14:50
///
/// @copyright	(c) David Gschwend, 2014
///

#include "SystemStates.h"

// Core library - IDE-based
#if defined(COSA)
#else // error
#error Platform not defined
#endif // end IDE

extern IOStream lcd;
extern SoundController sound_ctrl;
extern StateController system;
extern LuxMonitor lux_monitor;
extern TimeKeeper time_keeper;
extern LightController light_ctrl;
extern MP3Controller mp3_ctrl;
extern MAX7221 lcd_ctrl;

/////////////////////
//                 //
//  Startup State  //
//                 //
/////////////////////

// Implementation of Startup State
const prog_str* StartupState::toString(){ return PSTR("[StartupState]"); }
void StartupState::onEnter()        { lcd << PSTR("\n    &"); } // Heart Shape
void StartupState::onTimeout()      { system.change_state(&i_IdleState); };

void StartupState::onTouch(BUTTON button) {}
void StartupState::onIRMessage(IRMessage msg) {}
void StartupState::onSecondTick() {}
void StartupState::onLeave() {};



////////////////////
//                //
//   Idle State   //
//                //
////////////////////

const prog_str* IdleState::toString()    { return PSTR("[IdleState]"); }
void IdleState::onEnter() {
    time_keeper.printTime();
}
void IdleState::onTouch(BUTTON button) {
    // Todo: React on Touch Control
}
void IdleState::onIRMessage(IRMessage msg) {
    
    dark_ticks = 0;    // Restart Dark&Inactive Timer
    switch (msg) {
            
        // Up/Down: Change Volume
        case LEFT:
        case RIGHT:
            system.change_state(&i_SoundMenu);
            system.onIRMessage(msg);
            break;
            
        // Top/Down: Change Brightness/Light
        case UP:
        case DOWN:
            system.change_state(&i_LightMenu);
            system.onIRMessage(msg);
            break;
            
        case PLAY:
            // Flash Display Brightness
            lux_monitor.brightness = 1024;
            // Toggle Maximum/Minimum Brightness
            if (light_ctrl.getLevel() > 127) light_ctrl.setLevel(0);
            else light_ctrl.setLevel(255);
            break;
        
        // MENU: Change Alarm
        case MENU:
            system.change_state(&i_AlarmMenu);
            break;
    }
}
void IdleState::onSecondTick() {
    
    // Check if it's time for the Alarm
    time_t now; time_t alarm;
    time_keeper.getTime(now); time_keeper.getAlarm(alarm);
    if (alarm.seconds) {
        if (alarm.hours == now.hours && alarm.minutes == now.minutes) {
            system.change_state(&i_AlarmState);
            return;
        }
    }
    
    // Turn Off Display when inactive for >= DISP_TIME_THRESHOLD seconds
    static bool disp_off = false;
    if (//lux_monitor.brightness < DISP_DARK_THRESHOLD &&
        light_ctrl.getLevel() < 6*8) {
        if (dark_ticks >= 2*DISP_TIME_THRESHOLD) {
            lcd << "\n"; disp_off = true;
        } else {
            dark_ticks++;
        }
    }
    else
    {
        // Activity and/or Brightness, keep going!
        dark_ticks = 0;
        
        // Update Display (Time) if necessary
        if (disp_off) { // display was previously off, print Time anyway!
            time_keeper.printTime();
            disp_off = false;
        } else {        // display was previously on, only print if needed
            time_keeper.printTimeIfChanged();
        }
    }
//
//    TRACE(disp_off);
//    TRACE(dark_ticks);
//    TRACE(lux_monitor.brightness);
    
}

void IdleState::onLeave() {};
void IdleState::onTimeout() {};





////////////////////
//                //
//   Sound Menu   //
//                //
////////////////////

const prog_str* SoundMenu::toString() {
    return PSTR("[SoundMenu]");
}
void SoundMenu::onEnter() {}
void SoundMenu::onTouch(BUTTON button) {
    // TODO: React on Touch Control
}
void SoundMenu::onIRMessage(IRMessage msg) {
    
    // Get current Volume
    uint8_t volume = sound_ctrl.getVolume();        // 0 (mute) to 80 (max)
    int8_t level = (volume < 49) ? 0 : volume - 49; // 0 (mute) to 31 (max)

    // Volume Increase (Key RIGHT)
    if (msg == RIGHT) level++;
    // Volume Decrease (Key LEFT)
    if (msg == LEFT) level--;
    // Volume ZERO
    if (msg == PLAY) {
        if (level > 0) {  // was not in mute --> save, mute
            pre_mute_lvl = level;
            level = 0;
        } else {            // was in mute --> restore
            level = pre_mute_lvl;
        }
    }
    // UP/DOWN: Change Light
    if (msg == UP || msg == DOWN) {
        system.change_state(&i_LightMenu);
        system.onIRMessage(msg);
        return;
    }
    
    // Constrain from 0 to 31
    if (level < 0) level = 0;
    if (level > 31) level = 31;
    
    // Volume between 49–80 or 0 (mute).
    volume = (level > 0) ? level + 49 : 0;
    sound_ctrl.setVolume(volume);

    lcd <<  PSTR("\nVol\t") << level;
    cout << PSTR("    Set level to ") << level << PSTR(", volume to ") << volume << endl;
}

void SoundMenu::onTimeout() {
    // leave back to Idle
    system.change_state(&i_IdleState);
}
void SoundMenu::onLeave() {};
void SoundMenu::onSecondTick() {};





////////////////////
//                //
//   Light Menu   //
//                //
////////////////////

const prog_str* LightMenu::toString() {
    return PSTR("[LightMenu]");
}
void LightMenu::onEnter() {
    // Todo: Update Display
}
void LightMenu::onTouch(BUTTON button) {
    // Todo: React on Touch Control
}
void LightMenu::onIRMessage(IRMessage msg) {
    
    // Get current Light Level
    uint8_t light_lvl = light_ctrl.getLevel()/8; // 0 to 31
    
    // Light UP
    if (msg == UP) if (light_lvl < 31) light_lvl++;
    // Light DOWN
    if (msg == DOWN)  if (light_lvl > 0) light_lvl--;
    
    // LEFT/RIGHT: Change Volume
    if (msg == RIGHT || msg == LEFT) {
        system.change_state(&i_SoundMenu);
        system.onIRMessage(msg);
        return;
    }
    
    // Light MIN/MAX
    if (msg == PLAY) {
        // If already pretty bright --> shut down
        if (light_lvl > 15) light_lvl = 0;
        // If already rather dark --> turn fully on
        else light_lvl = 31;
    }
    
    light_ctrl.setLevel(light_lvl*8);
    if (light_lvl == 31) light_ctrl.setLevel(255);  // top-up for level 31
    
    lcd <<  PSTR("\nLi\t") << light_lvl;
    cout << PSTR("    Set light to ") << light_lvl << PSTR("/31") << endl;
}
void LightMenu::onTimeout() {
    // Todo: leave back to Idle
    system.change_state(&i_IdleState);
}
void LightMenu::onLeave() {};
void LightMenu::onSecondTick() {};




////////////////////
//                //
//   Alarm Menu   //
//                //
////////////////////

const prog_str* AlarmMenu::toString() {
    return PSTR("[AlarmMenu]");
}
void AlarmMenu::onEnter() {
    
    // load last saved alarm
    time_keeper.getAlarm(new_alarm);

    // Display <ALARM> for 1 second.
    lcd << "\nALARM";
    delay(1000);
    
    // Enter ALARM settings menu.
    // First ask if Alarm should be on/off. Then edit HH:MM.
    setupState  = setActive;
    is_blinking = false;
    num_menu_messages = 0;
    updateDisplay();
}

void AlarmMenu::updateDisplay() {
    
    // Print Setting "on/off"
    if (setupState == setActive) {
        
        str_P state = PSTR("   ");
        
        if (!is_blinking) {
            // active/inactive saved in <seconds> field
            if (new_alarm.seconds) state = PSTR(" on");
            else state = PSTR("off");
        }

        cout << PSTR("Alarm State: ") << state << endl;
        lcd  << PSTR("\n ") << state;
    }
    
    // Print Alarm Time "HH:MM"
    if (setupState == setHours || setupState == setMinutes) {
        
        // Clear LCD Display
        lcd  << PSTR("\n");
        
        // Print Time "HH:MM"
        char* hh = "HH";
        char* mm = "MM";
        
        hh[0] = new_alarm.hours/10 + '0';
        hh[1] = new_alarm.hours%10 + '0';
        mm[0] = new_alarm.minutes/10 + '0';
        mm[1] = new_alarm.minutes%10 + '0';
        
        if (! (setupState == setHours && is_blinking)) {
            // Hours not blinking, print
            lcd_ctrl.set_cursor(2, 0);
            lcd << hh;
        }
        // Print Separator
        lcd_ctrl.set_cursor(12, 0);
        lcd << ':';
        if  (! (setupState == setMinutes && is_blinking)) {
            // Mins not blinking, print
            lcd_ctrl.set_cursor(14, 0);
            lcd << mm;
        }
        
        cout << PSTR("    New Alarm: ") << hh << ':' << mm << endl;
    }
}

void AlarmMenu::onIRMessage(IRMessage msg) {
    
    // Menu Message: short --> Cancel / long --> TimeMenu
    // Actual Transition handled in onSecondTick()
    if (msg == MENU) {
        // count messages, switch when button released
        num_menu_messages++;
        last_millis_menu_pressed = RTC::millis();
    }
    // reset count if any other button pressed.
    else num_menu_messages = 0;

    // PLAY Message: Confirm Settings
    if (msg == PLAY) {
        // Save Alarm Settings
        time_keeper.setAlarm(new_alarm);
        
        // Inform User
        cout << PSTR("    Save Alarm Settings ") << new_alarm;
        cout << (new_alarm.seconds?PSTR(" ON"):PSTR(" OFF")) << endl;
        lcd << PSTR("\nSAVED");
        delay(500);
        
        // Leave
        system.change_state(&i_IdleState);
        return;
    }
    
    // State: Activate/Deactivate
    if (setupState == setActive) {
        // Change Setting
        if (msg == UP || msg == DOWN)
            new_alarm.seconds = !new_alarm.seconds;
        // Next Setting
        // Switch to Hours/Minutes only possible when alarm activated
        if (msg == RIGHT && new_alarm.seconds)
            setupState = setHours;
    }
    // State: Set Hours
    else if (setupState == setHours) {
        // Change Setting
        if (msg == UP) {
            if (new_alarm.hours < 23) new_alarm.hours++;
            else new_alarm.hours = 0;
        }
        if (msg == DOWN) {
            if (new_alarm.hours > 0) new_alarm.hours--;
            else new_alarm.hours = 23;
        }
        // Next Setting
        if (msg == RIGHT) setupState = setMinutes;
        if (msg == LEFT)  setupState = setActive;
    }
    // State: Set Minutes
    else if (setupState == setMinutes) {
        // Change Setting
        if (msg == UP) {
            if (new_alarm.minutes < 59) new_alarm.minutes++;
            else new_alarm.minutes = 0;
        }
        if (msg == DOWN) {
            if (new_alarm.minutes > 0) new_alarm.minutes--;
            else new_alarm.minutes = 59;
        }
        // Next Setting
        if (msg == LEFT) setupState = setHours;
    }
    
    updateDisplay();

}
void AlarmMenu::onSecondTick() {
    
    // If we had MENU messages
    // & last message is older than 100ms (button no longer pressed)
    if (num_menu_messages > 0 &&
        RTC::since(last_millis_menu_pressed) > 100) {
        
        //  short = cancel & leave to idle, long = time setting
        if (num_menu_messages < 10) system.change_state(&i_IdleState);
        else system.change_state(&i_TimeMenu);
        
        return;
    }
    
    // Blink currently edited field
    is_blinking = !is_blinking;
    updateDisplay();
    
};

void AlarmMenu::onTimeout() {}; // no timeout defined
void AlarmMenu::onLeave() {};
void AlarmMenu::onTouch(BUTTON button) {};



////////////////////
//                //
//   Time Menu    //
//                //
////////////////////

const prog_str* TimeMenu::toString() {
    return PSTR("[TimeMenu]");
}
void TimeMenu::onEnter() {
    
    // load last saved alarm
    time_keeper.getTime(new_time);
    
    // Display <TIME> for 1 second.
    lcd << PSTR("\nTIME");
    sleep(1);
    
    // Enter TIME settings menu.
    // First edited is hours in HH:MM
    setupState = setHours;
    is_blinking = false;
    updateDisplay();
}

void TimeMenu::updateDisplay() {
    
    // Clear LCD Display
    lcd  << PSTR("\n");

    // Print Time "HH:MM"
    char* hh = "HH";
    char* mm = "MM";

    hh[0] = new_time.hours/10 + '0';
    hh[1] = new_time.hours%10 + '0';
    mm[0] = new_time.minutes/10 + '0';
    mm[1] = new_time.minutes%10 + '0';
    
    if (! (setupState == setHours && is_blinking)) {
        // Hours not blinking, print
        lcd_ctrl.set_cursor(2, 0);
        lcd << hh;
    }
    // Print Separator
    lcd_ctrl.set_cursor(12, 0);
    lcd << ':';
    if  (! (setupState == setMinutes && is_blinking)) {
        // Mins not blinking, print
        lcd_ctrl.set_cursor(14, 0);
        lcd << mm;
    }
    
    cout << PSTR("    New Time: ") << hh << ':' << mm << endl;
}

void TimeMenu::onTouch(BUTTON button) {
    // Todo: React on Touch Control
}
void TimeMenu::onIRMessage(IRMessage msg) {
    
    // MENU Message: Cancel
    if (msg == MENU) {
        // Only enable canceling after 1s
        system.change_state(&i_IdleState);
        return;
    }
    
    // PLAY Message: Confirm Settings
    if (msg == PLAY) {
        // Save Time Settings
        time_keeper.setTime(new_time);
        
        // Inform User
        cout << PSTR("    Save Time Settings: ") << new_time << endl;
        lcd  << PSTR("\nSAVED");
        delay(500);
        
        // Leave
        system.change_state(&i_IdleState);
        return;
    }
    
    // State: Set Hours
    if (setupState == setHours) {
        // Change Setting
        if (msg == UP) {
            if (new_time.hours < 23) new_time.hours++;
            else new_time.hours = 0;
            updateDisplay();
        }
        if (msg == DOWN) {
            if (new_time.hours > 0) new_time.hours--;
            else new_time.hours = 23;
            updateDisplay();
        }
        // Next Setting
        if (msg == RIGHT) setupState = setMinutes;
        if (msg == LEFT)  {}; // cannot go left
    }
    
    // State: Set Minutes
    else if (setupState == setMinutes) {
        // Change Setting
        if (msg == UP) {
            if (new_time.minutes < 59) new_time.minutes++;
            else new_time.minutes = 0;
        }
        if (msg == DOWN) {
            if (new_time.minutes > 0) new_time.minutes--;
            else new_time.minutes = 59;
        }
        // Next Setting
        if (msg == RIGHT) {}; // cannot go right
        if (msg == LEFT)  setupState = setHours;
    }
    
    updateDisplay();

}
void TimeMenu::onSecondTick() {
    is_blinking = !is_blinking;
    updateDisplay();
};
void TimeMenu::onTimeout() {}; // no timeout defined
void TimeMenu::onLeave() {};



////////////////////
//                //
//   Alarm State  //
//                //
////////////////////

const prog_str* AlarmState::toString() {
    return PSTR("[AlarmState]");
}
void AlarmState::onEnter() {
    // TODO:

    cout << PSTR("    ===========") << endl;
    cout << PSTR("    | WAKE UP |") << endl;
    cout << PSTR("    ===========") << endl;
    
    lcd << PSTR("\n  HI &"); // Hi ♡

    // Change Volume to 0
    // Change Light to 0
    sound_ctrl.setVolume(0);
    light_ctrl.setLevel(0);
    // Change to MP3 Playback
    // Activate Amplifier
    sound_ctrl.startMP3();
    
    // Save Time when Wakeup started:
    time_t now; time_keeper.getTime(now);
    start_time = (clock_t) now;
    
    delay(2000);
    
    time_keeper.printTime();
}
void AlarmState::onTouch(BUTTON button) {
    // Todo: React on Touch Control
}
void AlarmState::onIRMessage(IRMessage msg) {
    
    // IR Reaction -> Woken up.
    system.change_state(&i_IdleState);

}
void AlarmState::onTimeout() {}; // no timeout defined
void AlarmState::onLeave() {
    
    // Turn Light at least to 40%
    if (light_ctrl.getLevel() < 100) light_ctrl.setLevel(100);
    
    // Turn Sound Off.
    sound_ctrl.setVolume(0);
    delay(100);
    sound_ctrl.stopMP3();
    
    // Deactivate Alarm
    time_t alarm; time_keeper.getAlarm(alarm);
    alarm.seconds = false; // deactivate
    time_keeper.setAlarm(alarm);
    
    // Good Morning Message
    cout << PSTR("  Have a great Day!") << endl;
    lcd << PSTR("\n HELLO");
    delay(1000);
    lcd << PSTR("\n MY &"); // My <heart>
    delay(1500);
    
};

void AlarmState::onSecondTick() {
    
    time_t now; time_keeper.getTime(now);
    uint32_t seconds_passed = ((clock_t) now) - start_time;
    
    // After Wakeup Duration + 60 Seconds Warning Blinking, leave Alarm Mode.
    if (seconds_passed > wakeup_duration + 60) {
        system.change_state(&i_IdleState);
        return;
    }
    
    // Alarm Blinking when not stopped after Wakeup Time elapsed
    if (seconds_passed > wakeup_duration) {
        if (light_ctrl.getLevel()) light_ctrl.setLevelImmediately(0);
        else light_ctrl.setLevelImmediately(255);
        return;
    }
    
    
    // Slow Wakeup-Fade of Light and Sound (0 to 100%)
    /*
     *     ^ light
     *     | +snd                                    .'
     *     |                                       .'
     *     |                                     .'
     *     |                                   .'
     *     |                                 .'
     *     |                               .'
     *     |                             .'
     *     |                           .'
     *     |                          '
     *     |                    ...'''
     *     |              ...'''
     *     |        ...'''
     *     |  ...'''                50                   100
     *     -------------------------|---------------------|> level (= % of Time)
     */
    
    // First half slow, second half fast (hand-tuned)

    uint8_t  level = (100*seconds_passed)/wakeup_duration;
    if (level < 50) {
        light_ctrl.setLevel(level+level/2);  // 0 to 75 (of 255)
        sound_ctrl.setVolume(level/5+25);    // 25 to 35 (of 80)
    } else {
        light_ctrl.setLevel((level-50)*3+75);  // 75 to 225 (of 255)
        sound_ctrl.setVolume((level-50)/2+35); // 35 to 60 (of 80)
    }
    
    cout << PSTR("Wakeup Level: ") << level << PSTR("%") << endl;
    
    // Update Display (Time) if necessary
    time_keeper.printTimeIfChanged();
    
    // Add wakeup indicator (leftmost column)
    lcd_ctrl.set_column(0, (1 << (level/12)));  // dot in px 0-7 (max reached @84%)

};





// Create Singleton Instance for each state
StartupState i_StartupState;
IdleState i_IdleState;
LightMenu i_LightMenu;
AlarmMenu i_AlarmMenu;
AlarmState i_AlarmState;
TimeMenu  i_TimeMenu;
SoundMenu i_SoundMenu;

