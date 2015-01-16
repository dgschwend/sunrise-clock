///
/// @file		StateController.h
/// @brief		System State Machine Controller
/// @n
/// @n @b		Project SunriseClock
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		David Gschwend
///
/// @date		28.08.14 20:25
///
/// @copyright	(c) David Gschwend, 2014
///

#include "Cosa/RTC.hh"
#include "Cosa/Periodic.hh"
#include "Cosa/Trace.hh"

#include "SystemState.h"

extern IOStream cout;

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

///
/// @brief  State Machine Controller
///
class StateController : private Periodic {
public:
    
    /// @brief  Constructor
    /// @param  initialState from which state we want to start
    StateController(SystemState* initialState) :
    currentState(initialState), Periodic(128) {
    };
    
    /// @brief      Traverse to the next System State
    /// @details    Calls Leave/Enter on the prev/next State.
    void change_state(SystemState *newState);
    
    void begin();
        
    void onIRMessage(SystemState::IRMessage message);
    
    void onTouch(SystemState::BUTTON button);
    
    /// @brief RTC millis on entering of current state (for timeout)
    uint32_t                millis_on_state_enter;

private:
    /// @brief The current System State
    SystemState             *currentState;
    /// @brief Last received IR Message, retriggered on REPEAT msg.
    SystemState::IRMessage  last_IR_message;
    // Holdoff for REPEAT in the first <REPEAT_HOLDOFF>*32 ms
    static const uint16_t REPEAT_HOLDOFF = 6;
    uint16_t num_repeats_received;
    
    /// @brief Interrupt sent periodically. Used to trigger SystemState::onSecondTick() and SystemState::onTimeout()
    virtual void run();
};

//extern StateController system;

#endif
