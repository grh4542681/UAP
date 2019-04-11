#include <stdio.h>
#include <string.h>
#include <time.h>

#include "time_c.h"

namespace util::time {

TimeC::TimeC()
{

}

TimeC::TimeC(struct timeval* tv, struct timezone* tz)
{
    if (tv) {
        tv_.tv_sec = tv->tv_sec;
        tv_.tv_usec = tv->tv_usec;
    }
    if (tz) {
        tz_.tz_minuteswest = tz->tz_minuteswest;
        tz_.tz_dsttime = tz->tz_dsttime;
    }
}

TimeC::TimeC(const TimeC& other)
{
    tv_.tv_sec = other.tv_.tv_sec;
    tv_.tv_usec = other.tv_.tv_usec;

    tz_.tz_minuteswest = other.tz_.tz_minuteswest;
    tz_.tz_dsttime = other.tz_.tz_dsttime;
}

TimeC::~TimeC()
{

}

TimeC& TimeC::operator=(const TimeC& other)
{
    tv_.tv_sec = other.tv_.tv_sec;
    tv_.tv_usec = other.tv_.tv_usec;

    tz_.tz_minuteswest = other.tz_.tz_minuteswest;
    tz_.tz_dsttime = other.tz_.tz_dsttime;
    return *this;
}

TimeC TimeC::GetCurrTime()
{
    struct timeval tv;
    memset(&tv, 0, sizeof(struct timeval));
    if (gettimeofday(&tv, NULL)) {
        return TimeC(&tv, NULL);
    }
    return TimeC(&tv, NULL);
}

void TimeC::print()
{
    struct tm* ptm = localtime(&tv_.tv_sec);
    printf("%d-%d-%d %d:%d:%d.%ld\n",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min,ptm->tm_sec,tv_.tv_usec);
}

}

