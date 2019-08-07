#ifndef __TIME_RETURN_H__
#define __TIME_RETURN_H__

#include "return.h"

namespace timer {

class TimeRet : public ret::Return {
public:
    enum ECode{
        TIME_EBASE = TIME_ERROR_CODE_BASE,
        TIME_EGET,
    };
public:
    static ECodeMapType ECodeMap;
public:
    TimeRet(int err_code = 0) : ret::Return(err_code) {
        err_code_vec_.push_back(&TimeRet::ECodeMap);
    }
    TimeRet(TimeRet& other) : ret::Return(other) { }
    ~TimeRet() { };
public:
    TimeRet& operator=(const int err_code) {
        Return::operator=(err_code);
        return *this;
    }   
    TimeRet& operator=(const TimeRet& ret) {
        Return::operator=(ret);
        return *this;
    }   
    TimeRet& operator=(const TimeRet&& ret) {
        Return::operator=(ret);
        return *this;
    }
};

}

#endif
