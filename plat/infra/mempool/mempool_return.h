#ifndef __MEMPOOL_RETURN_H__
#define __MEMPOOL_RETURN_H__

#include "return.h"

namespace mempool {

/**
 * @brief Memory pool return value.
 */
class MemPoolRet : public ret::Return {
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
    MemPoolRet(int err_code = 0) : ret::Return(err_code) {
        err_code_vec_.push_back(&MemPoolRet::ECodeMap);
    }
    MemPoolRet(MemPoolRet& other) : ret::Return(other) { }
    ~MemPoolRet() { };
public:
    MemPoolRet& operator=(int err_code) {
        Return::operator=(err_code);
        return *this;
    }   
    MemPoolRet& operator=(MemPoolRet& ret) {
        Return::operator=(ret);
        return *this;
    }   
    MemPoolRet& operator=(MemPoolRet&& ret) {
        Return::operator=(ret);
        return *this;
    }
};

}

#endif
