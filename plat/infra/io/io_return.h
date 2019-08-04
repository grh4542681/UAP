#ifndef __IO_RETURN_H__
#define __IO_RETURN_H__

#include "return.h"

namespace io {

class IoRet : public ret::Return {
public:
    enum ECode{
        EFDTYPE = IO_ERROR_CODE_BASE,
    };
public:
    static ECodeMapType ECodeMap;
public:
    IoRet(int err_code) : ret::Return(err_code) {
        err_code_vec_.push_back(&IoRet::ECodeMap);
    }
    ~IoRet() { };
};

}

#endif
