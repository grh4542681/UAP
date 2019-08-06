#ifndef __REPORT_RETURN_H__
#define __REPORT_RETURN_H__

#include "return.h"

namespace report {

class ReportRet : public ret::Return {
public:
    enum ECode{
        REPORT_EBASE = REPORT_ERROR_CODE_BASE,
    };
public:
    static ECodeMapType ECodeMap;
public:
    ReportRet(int err_code = 0) : ret::Return(err_code) {
        err_code_vec_.push_back(&ReportRet::ECodeMap);
    }
    ReportRet(ReportRet& other) : ret::Return(other) { }
    ~ReportRet() { };
public:
    ReportRet& operator=(const int err_code) {
        Return::operator=(err_code);
        return *this;
    }   
    ReportRet& operator=(const ReportRet& ret) {
        Return::operator=(ret);
        return *this;
    }   
    ReportRet& operator=(const ReportRet&& ret) {
        Return::operator=(ret);
        return *this;
    }
};

}

#endif
