#ifndef __TIME_C_H__
#define __TIME_C_H__

#include <sys/time.h>

#include "time_return.h"
#include "vtime.h"

namespace timer {
class TimeC : public Time {
public:
    TimeC();
    ~TimeC();
    TimeC(const TimeC& other);

    TimeC& operator=(const TimeC& other);

    std::string Format(std::string format);
    TimeRet GetCurrTime();

private:
    struct timespec tp_;
};

/**
* @brief To - Convert to struct timespec.
*
* @param [p] - Pointer of struct timespec.
*
* @returns  TimeRet.
*/
template < > TimeRet Time::To<struct timespec>(struct timespec* p);
template < > TimeRet Time::To<struct timeval>(struct timeval* p);

/**
 * @brief Now - Get current system time
 *
 * @returns  Time class instance.
 */
TimeC NowC();

}

#endif
