#ifndef __BITMAP_RETURN_H__
#define __BITMAP_RETURN_H__

#include "return.h"

namespace util::bitmap {

class BitmapRet : public ret::Return {
public:
    enum ECode{
        BM_EBASE = BM_ERROR_CODE_BASE,
        BM_EOUTBOUND,
    };
public:
    static ECodeMapType ECodeMap;
public:
    BitmapRet(int err_code = 0) : ret::Return(err_code) {
        err_code_vec_.push_back(&BitmapRet::ECodeMap);
    }
    BitmapRet(BitmapRet& other) : ret::Return(other) { }
    ~BitmapRet() { };
public:
    BitmapRet& operator=(const int err_code) {
        Return::operator=(err_code);
        return *this;
    }   
    BitmapRet& operator=(const BitmapRet& ret) {
        Return::operator=(ret);
        return *this;
    }   
    BitmapRet& operator=(const BitmapRet&& ret) {
        Return::operator=(ret);
        return *this;
    }
};

}

#endif
