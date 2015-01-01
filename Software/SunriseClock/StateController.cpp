///
/// @file		StateController.cpp
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

#include "StateController.h"

void StateController::change_state(SystemState *newState) {
    cout << PSTR("System: Transition ") << currentState->toString() << PSTR(" -> ") << newState->toString() << endl;
    currentState->onLeave();
    currentState = newState;
    millis_on_state_enter = RTC::millis();
    currentState->onEnter();
}

void StateController::run() {
    // called by Periodic every <ms> ms.
    static uint32_t millis_on_last_call = 0;
    
    // Check one-second Tick Condition:
    if (RTC::since(millis_on_last_call) > 500) {
        //trace << PSTR("SC: second-tick\r\n");
        millis_on_last_call = RTC::millis();
        currentState->onSecondTick();
    }
    
    // Check timeout Condition (if timeout > 0):
    if ((currentState->timeout_ms() > 0) &&
        (RTC::since(millis_on_state_enter) > currentState->timeout_ms())
        ) {
        //trace << PSTR("SC: timeout\r\n");
        currentState->onTimeout();
    }
}

void StateController::begin() {
    cout << PSTR("System: Started up.\r\n");
    Periodic::begin();  // Start Periodic Timer
    millis_on_state_enter = RTC::millis();
    this->currentState->onEnter();
}

void StateController::onIRMessage(SystemState::IRMessage message) {
    
    cout << PSTR("System: onIRmsg in ") <<
    this->currentState->toString() << endl; // log message
    millis_on_state_enter = RTC::millis(); // delay timeout
    
    // Recall last action on REPEAT.
    if (message == SystemState::REPEAT) { message = last_IR_message; }
    last_IR_message = message;  // remember last action.
    
    currentState->onIRMessage(message);
}

void StateController::onTouch(SystemState::BUTTON button) {
    cout << PSTR("System: onTouch in ") <<
    this->currentState->toString() << endl; // log message
    millis_on_state_enter = RTC::millis();  // delay timeout
    
    currentState->onTouch(button);
}

