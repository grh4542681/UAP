#ifndef __TIME_CPP_H__
#define __TIME_CPP_H__

#include "time_return.h"
#include "vtime.h"

namespace util::time {

class TimeCpp : public Time {
public:
    TimeCPP();
    ~TimeCpp();

    std::string Format(std::string format);
    TimeRet GetCurrTime();
};

TimeCpp NowCpp() {
    TimeCpp tm;
    tm.GetCurrTime();
    return tm;
}

}

#endif
