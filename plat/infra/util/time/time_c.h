#ifndef __TIME_C_H__
#define __TIME_C_H__

#include <sys/time.h>

#include "time_return.h"
#include "vtime.h"

namespace util::time {
class TimeC : public Time {
public:
    TimeC();
    ~TimeC();
    TimeC(const TimeC& other);

    TimeC& operator= (const TimeC& other);

    std::string Format(std::string format);
    TimeRet GetCurrTime();

private:
    struct timespec tp_;
};

/**
 * @brief Now - Get current system time
 *
 * @returns  Time class instance.
 */
TimeC NowC() {
    TimeC tm; 
    tm.GetCurrTime();
    return tm; 
}

}

#endif
