#ifndef __TIMER_RETURN_H__
#define __TIMER_RETURN_H__

#include "return.h"

namespace timer {

class TimerRet : public ret::Return {
public:
    enum ECode{
        TIMER_EBASE = TIMER_ERROR_CODE_BASE,
        TIMER_EGET,
    };
public:
    static ECodeMapType ECodeMap;
public:
    TimerRet(int err_code = 0) : ret::Return(err_code) {
        err_code_vec_.push_back(&TimerRet::ECodeMap);
    }
    TimerRet(TimerRet& other) : ret::Return(other) { }
    ~TimerRet() { };
public:
    TimerRet& operator=(const int err_code) {
        Return::operator=(err_code);
        return *this;
    }   
    TimerRet& operator=(const TimerRet& ret) {
        Return::operator=(ret);
        return *this;
    }   
    TimerRet& operator=(const TimerRet&& ret) {
        Return::operator=(ret);
        return *this;
    }
};

}

#endif
