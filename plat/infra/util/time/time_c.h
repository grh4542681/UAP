#ifndef __TIME_C_H__
#define __TIME_C_H__

#include <sys/time.h>

#include "time_return.h"

namespace util::time {

class TimeC {
public:
    TimeC();
    ~TimeC();
    TimeC(const TimeC& other);

    TimeC& operator= (const TimeC& other);
    void print();

    static TimeC GetCurrTime();

private:
    TimeC(struct timeval* tv, struct timezone* tz);

    struct timeval tv_;
    struct timezone tz_;

};

}

#endif
