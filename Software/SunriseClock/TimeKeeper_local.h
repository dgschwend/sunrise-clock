///
/// @file		TimeKeeper.h
/// @n
/// @n @b		Project SunriseClock
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		David Gschwend
///
/// @date		02.09.14 17:19
/// @copyright	(c) David Gschwend, 2014
///

/**
 * Wrapper Class for Time-Management using local RTC timer
 *
 **/

/*
 
// Core library - IDE-based
#if defined(COSA)
#else // error
#error Platform not defined
#endif // end IDE

#include "Cosa/Board.hh"
#include "Cosa/Periodic.hh"
#include "Cosa/Time.hh"
extern IOStream lcd;
extern IOStream cout;

#ifndef TimeKeeper_h
#define TimeKeeper_h

/// @brief    TimeKeeper Class -- get and set time internally, increment seconds using timer0.
class TimeKeeper : public Periodic {
    
public:
   
    /// @brief  Constructor:
    TimeKeeper() : Periodic(16), minutes_on_last_print(128) {};
    
    // @brief Set Time
    void setTime(time_t new_time);
    void setTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec);
    
    // @brief Get time_t struct
    time_t getTime();
    
    /// Use internal RTC counter...
    /// @brief  Method is called periodically, increments Time
    virtual void run();
    
    // @brief Print given time to LCD/cout
    void printTime(time_t* now);
    
    // @brief Print current time to LCD/cout
    void printTime();
    
    // @brief Print current time to LCD/cout if changed since last print
    void printTimeIfChanged();
    
private:
    clock_t  m_time;
    uint8_t  minutes_on_last_print;
};

#endif
 */
