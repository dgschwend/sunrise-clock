///
/// @file		SystemState.h
/// @brief		Actual System State Implementations
/// @n
/// @n @b		Project SunriseClock
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		David Gschwend
/// @date		02.09.14 14:50
///
/// @copyright	(c) David Gschwend, 2014
///

#include "SystemState.h"
#include "StateController.h"
#include "SoundController.h"
#include "LuxMonitor.h"
#include "TimeKeeper.h"
#include "LightController.h"
#include "MP3Controller.h"
#include "Cosa/Trace.hh"
#include "MAX7221.h"

// Core library - IDE-based
#if defined(COSA)
#else // error
#error Platform not defined
#endif // end IDE

///////// CONFIG
////////////////////////////
// Timeout for Leaving Sound/Light Menus
#define MENU_TIMEOUT 1000
// Number of Minutes until Wakeup
#define WAKEUP_TIME_MIN 19
// Brightness & Time (seconds) Threshold for turning off Display
#define DISP_DARK_THRESHOLD 15
#define DISP_TIME_THRESHOLD 10

#ifndef SystemStates_h
#define SystemStates_h

class StartupState  : public SystemState {
    const prog_str* toString();
    void onEnter();
    void onLeave();
    void onTouch(BUTTON button);
    void onIRMessage(IRMessage msg);
    void onSecondTick();
    void onTimeout();
    const uint16_t timeout_ms() {return 1000;}
};
class IdleState  : public SystemState {
    const prog_str* toString();
    void onEnter();
    void onLeave();
    void onTouch(BUTTON button);
    void onIRMessage(IRMessage msg);
    void onSecondTick();
    void onTimeout();
    const uint16_t timeout_ms() {return 0;}
    uint16_t dark_ticks;
};
class SoundMenu  : public SystemState {
    const prog_str* toString();
    void onEnter();
    void onLeave();
    void onTouch(BUTTON button);
    void onIRMessage(IRMessage msg);
    void onSecondTick();
    void onTimeout();
    const uint16_t timeout_ms() {return MENU_TIMEOUT;}
    uint8_t pre_mute_lvl;
};
class LightMenu  : public SystemState {
    const prog_str* toString();
    void onEnter();
    void onLeave();
    void onTouch(BUTTON button);
    void onIRMessage(IRMessage msg);
    void onSecondTick();
    void onTimeout();
    const uint16_t timeout_ms() {return MENU_TIMEOUT;}
};

class AlarmMenu  : public SystemState {
    const prog_str* toString();
    void onEnter();
    void onLeave();
    void onTouch(BUTTON button);
    void onIRMessage(IRMessage msg);
    void onSecondTick();
    void onTimeout();
    const uint16_t timeout_ms() {return 0;}
    
    void updateDisplay();
    
    // Edited Alarm Time. Setting "active/not active" saved in <seconds> field.
    time_t new_alarm;
    // Toggle variable (500ms) for blinking current edit field.
    bool is_blinking;
    // States during editing...
    enum AlarmSetupStateType {
        setHours, setMinutes, setActive
    } setupState;
    // Count number of "MENU" IR Messages and SecondTicks received to see if button is pressed long (--> change to TimeMenu, else Cancel)
    uint8_t num_menu_messages;
    uint32_t last_millis_menu_pressed;
};

class TimeMenu   : public SystemState {
    const prog_str* toString();
    void onEnter();
    void onLeave();
    void onTouch(BUTTON button);
    void onIRMessage(IRMessage msg);
    void onSecondTick();
    void onTimeout();
    const uint16_t timeout_ms() {return 0;}
    
    void updateDisplay();
    
    // Edited Date/Time.
    time_t new_time;
    // Toggle variable (500ms) for blinking current edit field.
    bool is_blinking;
    // States during editing...
    enum TimeSetupStateType {
        setHours, setMinutes
    } setupState;
};

class AlarmState : public SystemState {
    const prog_str* toString();
    void onEnter();
    void onLeave();
    void onTouch(BUTTON button);
    void onIRMessage(IRMessage msg);
    void onSecondTick();
    void onTimeout();
    const uint16_t timeout_ms() {return 0;}
    
    // DURATION OF WAKEUP (seconds)
    static const uint16_t wakeup_duration = WAKEUP_TIME_MIN*60;
    clock_t start_time;
};

extern StartupState i_StartupState;
extern IdleState i_IdleState;
extern SoundMenu i_SoundMenu;
extern LightMenu i_LightMenu;
extern AlarmMenu i_AlarmMenu;
extern AlarmState i_AlarmState;
extern TimeMenu i_TimeMenu;

#endif
