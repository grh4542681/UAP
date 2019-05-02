#include <stdio.h>
#include <string.h>
#include <time.h>

#include "time_c.h"

namespace util::time {

TimeC::TimeC() : Time()
{
    memset(&tp_, 0, sizeof(struct timespec));
}

TimeC::TimeC(const TimeC& other) : Time(other)
{
    memset(&tp_, 0, sizeof(struct timespec));
    tp_.tv_sec = other.tp_.tv_sec;
    tp_.tv_nsec = other.tp_.tv_nsec;
}

TimeC::~TimeC()
{

}

TimeC& TimeC::operator=(const TimeC& other)
{
    Time::operator=(other);
    memset(&tp_, 0, sizeof(struct timespec));
    tp_.tv_sec = other.tp_.tv_sec;
    tp_.tv_nsec = other.tp_.tv_nsec;
    return *this;
}

template < >
TimeRet Time::To<struct timespec>(struct timespec* p)
{
    p->tv_sec = second_;
    p->tv_nsec = nanosecond_;
    return TimeRet::SUCCESS;
}

std::string TimeC::Format(std::string format) {
    std::string str;
    char buff[1024];
    memset(buff, 0, sizeof(buff));

    if (!strftime(buff, sizeof(buff), format.c_str(), localtime(&second_))) {
        memset(buff, 0, sizeof(buff));
    }
    str.assign(buff);
    return str;
}

TimeRet TimeC::GetCurrTime()
{
    if (clock_gettime(CLOCK_REALTIME, &tp_) < 0) {
        return TimeRet::ETIMEGET;
    }
    second_ = tp_.tv_sec;
    nanosecond_ = tp_.tv_nsec;
    return TimeRet::SUCCESS;
}
 
TimeC NowC() {
    TimeC tm; 
    tm.GetCurrTime();
    return tm; 
}

}

