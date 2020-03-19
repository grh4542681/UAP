#ifndef __MEMPOOL_RETURN_H__
#define __MEMPOOL_RETURN_H__

#include "return.h"

namespace mempool {

/**
 * @brief Memory pool return value.
 */
class MempoolRet : public ret::Return {
public:
    enum ECode{
        //memort
        EALLOC,

        //busy list
        EBUSYLISTINSERT,
        EBUSYLISTNOTFOUND,
        EBUSYLISTDUPADDRESS,
    };
public:
    static ECodeMapType ECodeMap;
public:
    MempoolRet(int err_code = 0) : ret::Return(err_code) {
        err_code_vec_.push_back(&MempoolRet::ECodeMap);
    }
    MempoolRet(MempoolRet& other) : ret::Return(other) { }
    ~MempoolRet() { };
public:
    MempoolRet& operator=(int err_code) {
        Return::operator=(err_code);
        return *this;
    }   
    MempoolRet& operator=(MempoolRet& ret) {
        Return::operator=(ret);
        return *this;
    }   
    MempoolRet& operator=(MempoolRet&& ret) {
        Return::operator=(ret);
        return *this;
    }
};

}

#endif
