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

// Core library - IDE-based
#if defined(COSA)
#else // error
#error Platform not defined
#endif // end IDE

#include "Cosa/Board.hh"
#include "Cosa/Periodic.hh"
#include "Cosa/TWI/Driver/DS1307.hh"
#include "Cosa/Time.hh"
extern IOStream lcd;
extern IOStream cout;

#ifndef TimeKeeper_h
#define TimeKeeper_h

/**
 * Time-Management Class either with DS1307 Real-Time Clock or with internal Timer.
 * Allows setting/getting Time and Alarm.
 *
 * @section Circuit
 * @code
 *                       TinyRTC(DS1307)
 *                       +------------+
 *                     1-|SQ          |
 *                     2-|DS        DS|-1
 * (A5/SCL)------------3-|SCL      SCL|-2
 * (A4/SDA)------------4-|SDA      SDA|-3
 * (VCC)---------------5-|VCC      VCC|-4
 * (GND)---------------6-|GND      GND|-5
 *                     7-|BAT         |
 *                       +------------+
 * @endcode
 **/

// USE_RTC_CHIP = 1: Use DS1307 Realtime Clock
// USE_RTC_CHIP = 0: Use internal Timer (less accurate, volatile settings!)
#define USE_RTC_CHIP 1

/// @brief    TimeKeeper Class -- Manage Time and Alarm Setting/Getting
#if USE_RTC_CHIP
class TimeKeeper {
#else
class TimeKeeper : private Periodic {
#endif

public:
    /// @brief  Constructor:
#if USE_RTC_CHIP
    TimeKeeper() : minutes_on_last_print(61) {};
#else
    TimeKeeper() : minutes_on_last_print(61), Periodic(1024) {};
#endif
    
    // @brief Set Time
    void setTime(time_t new_time);
    void setTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec);
    
    // @brief Read current time from RTC. Return 1 if successful, 0 otherwise.
    bool getTime(time_t& now);
    
    // @brief Print given time to LCD/cout
    void printTime(time_t& now);
    
    // @brief Print current time to LCD/cout
    void printTime();
    
    // @brief Print current time to LCD/cout if minutes have changed since last print (to avoid 1Hz flicker in Display)
    void printTimeIfChanged();
    
    // @brief Read Alarm from RTC memory. Return 1 if successful, 0 otherwise.
    bool getAlarm(time_t& alarm);
    
    // @brief Set Alarm (write to RTC memory).
    void setAlarm(time_t new_alarm);
    void setAlarm(uint8_t hour, uint8_t min, uint8_t sec);
    
private:
#if USE_RTC_CHIP
    DS1307   rtc_chip;
#else
    virtual void run();
    time_t   alarm_time;
    time_t   current_time;
#endif
    uint8_t  minutes_on_last_print;
};

#endif
