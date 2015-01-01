///
/// @file		LuxMonitor.cpp
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

#include "TimeKeeper.h"

// Getting / Setting Time

bool TimeKeeper::getTime(time_t& now) {
#if USE_RTC_CHIP
    // Time is saved in BCD, convert to Binary for calculations.
    bool status = rtc_chip.get_time(now);
    now.to_binary();
    if (status == 0) { cout << "ERROR: failed to get time from RTC!" << endl; }
    return status;
#else
    now.seconds =  current_time.seconds;
    now.minutes =  current_time.minutes;
    now.hours =    current_time.hours;
    now.day =      current_time.day;
    now.date =     current_time.date;
    now.month =    current_time.month;
    now.year =     current_time.year;
    return 1;
#endif
}

void TimeKeeper::setTime(time_t new_time) {
#if USE_RTC_CHIP
    // Time is delivered in Binary, convert to BCD for RTC chip.
    new_time.to_bcd();
    rtc_chip.set_time(new_time);
#else
    current_time.seconds =  new_time.seconds;
    current_time.minutes =  new_time.minutes;
    current_time.hours =    new_time.hours;
    current_time.day =      new_time.day;
    current_time.date =     new_time.date;
    current_time.month =    new_time.month;
    current_time.year =     new_time.year;
#endif
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
     
    setTime(new_time);
}

// Printing Time
void TimeKeeper::printTime(time_t& now) {
    
    minutes_on_last_print = now.minutes;
    
    char* time = "  :  ";
    time[0] = now.hours/10 + '0';
    time[1] = now.hours%10 + '0';
    time[3] = now.minutes/10 + '0';
    time[4] = now.minutes%10 + '0';
    
    cout << PSTR("The Time is ") << time << endl;
    lcd  << PSTR("\n ") << time;

}

void TimeKeeper::printTime() {
    time_t now; getTime(now);
    printTime(now);
}

// Print Time, but only if minutes have changed from last printout
// (to avoid 1Hz flicker in Display)
void TimeKeeper::printTimeIfChanged() {
    time_t now; getTime(now);
//    cout << PSTR("printTimeIfChanged ");
//    cout << PSTR("now: ") << now.minutes << PSTR(" last: ") << minutes_on_last_print << endl;
//    cout << PSTR("seconds: ") << now.seconds << endl;

    if (now.minutes != minutes_on_last_print) {
        minutes_on_last_print = now.minutes;
        printTime(now);
    }
}

// Get / Set Alarm
bool TimeKeeper::getAlarm(time_t& alarm) {
#if USE_RTC_CHIP
    // Alarm is always saved in Binary, no need for conversion.
    return rtc_chip.read(&alarm, sizeof(time_t), rtc_chip.RAM_START);
#else
    alarm.hours = alarm_time.hours;
    alarm.minutes = alarm_time.minutes;
    return 1;
#endif
}

void TimeKeeper::setAlarm(time_t new_alarm) {
#if USE_RTC_CHIP
    // Alarm is always saved in Binary, no need for conversion.
    rtc_chip.write(&new_alarm, sizeof(time_t), rtc_chip.RAM_START);
#else
    alarm_time.hours   = new_alarm.hours;
    alarm_time.minutes = new_alarm.minutes;
#endif
}

void TimeKeeper::setAlarm(uint8_t hour, uint8_t min, uint8_t sec) {
    time_t new_time  = time_t();
    new_time.minutes = min;
    new_time.hours   = hour;
    new_time.seconds = sec;
    setAlarm(new_time);
}

#if not USE_RTC_CHIP
void TimeKeeper::run() {    // Called every 1024 milliseconds
    time_t now;
    getTime(now);
    now.seconds++;
    if (now.seconds == 60) {now.seconds = 0; now.minutes++; }
    if (now.minutes == 60) {now.minutes = 0; now.hours++; }
    if (now.hours == 24) {now.hours = 0; }
    setTime(now);
}
#endif
