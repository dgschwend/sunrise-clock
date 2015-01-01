///
/// @file		TimeKeeper_local.cpp
/// @n
/// @n @b		Project SunriseClock
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		David Gschwend
///
/// @date		02.09.14 17:19
/// @copyright	(c) David Gschwend, 2014
///

/*
// Core library - IDE-based
#if defined(COSA)
#else // error
#error Platform not defined
#endif // end IDE

#include "TimeKeeper_local.h"

time_t TimeKeeper::getTime() {
    return time_t(m_time);
}

void TimeKeeper::setTime(time_t new_time) {
    m_time = clock_t(new_time);
}

void TimeKeeper::setTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) {
    
    //!< 00-59 Seconds.
    //!< 00-59 Minutes.
    //!< 00-23 Hours.
    //!< 01-07 Day. (ignored!?)
    //!< 01-31 Date.
    //!< 01-12 Month.
    //!< 00-99 Year.
    time_t new_time = time_t();
    new_time.seconds = sec;
    new_time.minutes = min;
    new_time.hours = hour;
    new_time.day = 0;
    new_time.date = day;
    new_time.month = month;
    new_time.year = year;
     
    m_time = clock_t(new_time);
}

/// @brief  Method is called periodically (every 16ms)
void TimeKeeper::run() {
    static uint8_t periods = 0;
    
    periods++;
    
    // increase number of seconds every (62+63)/2 = 62.5 calls = 1.00s
    if (((periods == 62) && !(m_time%2)) ||  // 992ms passed, odd second
        ((periods == 63) &&  (m_time%2)) )   // 1008ms passed, even second
    {
        m_time++;
    }
}

void TimeKeeper::printTime(time_t *now) {
    
    minutes_on_last_print = now->minutes;
    cout << PSTR("it's ");
    lcd  << PSTR("\n ");
    if (now->hours < 10) {
        cout << PSTR("0");
        lcd  << PSTR("0");
    }
    cout << now->hours << PSTR(":");
    lcd  << now->hours << PSTR(":");
    if (now->minutes < 10) {
        cout << PSTR("0");
        lcd  << PSTR("0");
    }
    cout << now->minutes << endl;
    lcd  << now->minutes;
}

void TimeKeeper::printTime() {
    time_t now = getTime();
    printTime(&now);
}

void TimeKeeper::printTimeIfChanged() {
    
    time_t now = getTime();
    if (now.minutes != minutes_on_last_print) {
        minutes_on_last_print = now.minutes;
        printTime(&now);
    }
    
}
*/
