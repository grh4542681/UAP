/*******************************************************
 * Copyright (C) For free.
 * All rights reserved.
 *******************************************************
 * @author   : Ronghua Gao
 * @date     : 2019-04-16 04:40
 * @file     : time.h
 * @brief    : Virtual class of time util.
 * @note     : Email - grh4542681@163.com
 * ******************************************************/
#ifndef __VTIME_H__
#define __VTIME_H__

#include <sys/time.h>

#include <string>

#include "time_return.h"

namespace util::time {

/**
* @brief - Virtual class Time
*/
class Time {
public:
    Time() {
        second_ = 0;
        nanosecond_ = 0;
    };
    Time(const Time& other) {
        second_ = other.second_;
        nanosecond_ = other.nanosecond_;
    }
    virtual ~Time() { };

    Time& operator= (const Time& other) {
        second_ = other.second_;
        nanosecond_ = other.nanosecond_;
        return *this;
    }

    Time& operator+ (const Time& other) {
        second_ += other.second_;
        nanosecond_ += other.nanosecond_;
        return *this;
    }
    Time& operator+ (const long second) {
        second_ += second_;
        return *this;
    }

    Time& operator- (const Time& other) {
        nanosecond_ -= other.nanosecond_;
        if (nanosecond_ < 0) {
            second_ -= 1;
            nanosecond_ += 1000000000;
        }
        second_ -= other.second_;
        return *this;
    }
    Time& operator- (const long second) {
        second_ -= second_;
        return *this;
    }

    Time& SetSecond(long second) {
        second_ = second;
        return *this;
    }

    Time& SetNanoSecond(long nsecond) {
        nanosecond_ = nsecond;
        return *this;
    }

    long GetSecond() {
        return second_;
    }

    long GetNanoSecond() {
        return nanosecond_;
    }

    /**
    * @brief Format - Format time and convert to a string.
    *
    * @param [format] - format.
    * %a     The abbreviated weekday name according to the current locale.
    * %A     The full weekday name according to the current locale.
    * %b     The abbreviated month name according to the current locale.
    * %B     The full month name according to the current locale.
    * %c     The preferred date and time representation for the current locale.
    * %C     The century number (year/100) as a 2-digit integer. (SU)
    * %d     The day of the month as a decimal number (range 01 to 31).
    * %D     Equivalent to %m/%d/%y.  (Yecch -- for Americans only.  Americans should note that in other countries %d/%m/%y is rather common.  This means that in international context  this
    *        format is ambiguous and should not be used.) (SU)
    * %e     Like %d, the day of the month as a decimal number, but a leading zero is replaced by a space. (SU)
    * %E     Modifier: use alternative format, see below. (SU)
    * %F     Equivalent to %Y-%m-%d (the ISO 8601 date format). (C99)
    * %G     The ISO 8601 week-based year (see NOTES) with century as a decimal number.  The 4-digit year corresponding to the ISO week number (see %V).  This has the same format and value
    *        as %Y, except that if the ISO week number belongs to the previous or next year, that year is used instead. (TZ)
    * %g     Like %G, but without century, that is, with a 2-digit year (00-99). (TZ)
    * %h     Equivalent to %b.  (SU)
    * %H     The hour as a decimal number using a 24-hour clock (range 00 to 23).
    * %I     The hour as a decimal number using a 12-hour clock (range 01 to 12).
    * %j     The day of the year as a decimal number (range 001 to 366).
    * %k     The hour (24-hour clock) as a decimal number (range 0 to 23); single digits are preceded by a blank.  (See also %H.)  (TZ)
    * %l     The hour (12-hour clock) as a decimal number (range 1 to 12); single digits are preceded by a blank.  (See also %I.)  (TZ)
    * %m     The month as a decimal number (range 01 to 12).
    * %M     The minute as a decimal number (range 00 to 59).
    * %n     A newline character. (SU)
    * %O     Modifier: use alternative format, see below. (SU)
    * %p     Either "AM" or "PM" according to the given time value, or the corresponding strings for the current locale.  Noon is treated as "PM" and midnight as "AM".
    * %P     Like %p but in lowercase: "am" or "pm" or a corresponding string for the current locale. (GNU)
    * %r     The time in a.m. or p.m. notation.  In the POSIX locale this is equivalent to %I:%M:%S %p.  (SU)
    * %R     The time in 24-hour notation (%H:%M). (SU) For a version including the seconds, see %T below.
    * %s     The number of seconds since the Epoch, that is, since 1970-01-01 00:00:00 UTC. (TZ)
    * %S     The second as a decimal number (range 00 to 60).  (The range is up to 60 to allow for occasional leap seconds.)
    * %t     A tab character. (SU)
    * %T     The time in 24-hour notation (%H:%M:%S). (SU)
    * %u     The day of the week as a decimal, range 1 to 7, Monday being 1.  See also %w.  (SU)
    * %U     The week number of the current year as a decimal number, range 00 to 53, starting with the first Sunday as the first day of week 01.  See also %V and %W.
    * %V     The ISO 8601 week number (see NOTES) of the current year as a decimal number, range 01 to 53, where week 1 is the first week that has at least 4 days in  the  new  year.   See
    *        also %U and %W.  (SU)
    * %w     The day of the week as a decimal, range 0 to 6, Sunday being 0.  See also %u.
    * %W     The week number of the current year as a decimal number, range 00 to 53, starting with the first Monday as the first day of week 01.
    * %x     The preferred date representation for the current locale without the time.
    * %X     The preferred time representation for the current locale without the date.
    * %y     The year as a decimal number without a century (range 00 to 99).
    * %Y     The year as a decimal number including the century.
    * %z     The time-zone as hour offset from GMT.  Required to emit RFC 822-conformant dates (using "%a, %d %b %Y %H:%M:%S %z"). (GNU)
    * %Z     The timezone or name or abbreviation.
    * %+     The date and time in date(1) format. (TZ) (Not supported in glibc2.)
    * %%     A literal '%' character.
    *
    * @returns  string time.
    */
    virtual std::string Format(std::string format) { std::string str = ""; return str; }

    /**
    * @brief GetCurrTime - Get current system time.
    */
    virtual TimeRet GetCurrTime() { return TimeRet::ESUBCLASS; }

    /**
    * @brief To - Convert to. Need to specialize in subclasses.
    *
    * @tparam [T] - Target type.
    * @param [p] - Target type pointer.
    *
    * @returns  TimeRet.
    */
    template < typename T >
    TimeRet To(T* p) { return TimeRet::ESUBCLASS; }

    bool IsPositive() {
        return !(second_ < 0 && nanosecond_ < 0);
    }

protected:
    long second_;        ///< seconds
    long nanosecond_;    ///< nanoseconds
};

}

#endif
