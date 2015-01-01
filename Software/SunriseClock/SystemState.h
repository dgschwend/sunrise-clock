///
/// @file		SystemState.h
/// @brief		Virtual SystemState Class
/// @details	Models a certain state in the System State Machine.
/// @n
/// @n @b		Project SunriseClock
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		David Gschwend
/// @date		02.09.14 14:50
///
/// @copyright	(c) David Gschwend, 2014
///

// Core library - IDE-based
#if defined(COSA)
#else // error
#error Platform not defined
#endif // end IDE

#include "Cosa/Types.h"

#ifndef SystemState_h
#define SystemState_h

/// @class Generic System State for the Controller State Machine
class SystemState {
public:
    /**
     * Possible Infrared Messages we can pass on.
     */
    enum IRMessage {
        UP          = 0x00,
        DOWN        = 0x01,
        RIGHT       = 0x02,
        LEFT        = 0x03,
        PLAY        = 0x04,
        MENU        = 0x05,
        REPEAT      = 0x06,
        ILLEGAL     = 0xFF
    };
    
    /// @brief  Possible Touch Button Types
    enum BUTTON {
        LightUp     = 0x00,
        LightDown   = 0x01,
        VolumeUp    = 0x02,
        VolumeDown  = 0x03
    };
  
public:
    ///	@brief Timeout for this State in Milliseconds.
    virtual const uint16_t timeout_ms() = 0;
    
    ///	@brief State Identification String
    virtual const prog_str* toString() = 0;
    
    ///	@brief Event: Entering this State.
    virtual void onEnter() = 0;
    
    ///	@brief Event: Leaving this State
    virtual void onLeave() = 0;
  
    ///	@brief Event: Touch Button was pressed.
    virtual void onTouch(BUTTON button) = 0;
    
    ///	@brief Event: Remote Control Message received.
    virtual void onIRMessage(IRMessage message) = 0;
    
    ///	@brief Event: The one-second system Tick occured.
    virtual void onSecondTick() = 0;
    
    ///	@brief Event: The user-defined timeout_ms elapsed since entering the state.
    virtual void onTimeout() = 0;
        
};

#endif
