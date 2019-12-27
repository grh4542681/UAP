#ifndef __IO_RETURN_H__
#define __IO_RETURN_H__

#include "return.h"

namespace io {

/**
* @brief - IO return value.
*/
class IoRet : public ret::Return {
public:
    /**
    * @brief - Io return value.
    */
    enum ECode{
        IO_EFDTYPE = IO_ERROR_CODE_BASE,
        IO_EUNKNOWFD,
        IO_EUNKNOWEVENT,
        IO_EMATCHEVENT,
        IO_EADDEVENT,
        IO_ENOCALLBACK,

        IO_EBADSELECTITEM,
        IO_ENOSELECTITEM,

        IO_EINPUTCB,
        IO_EOUTPUTCB,
        IO_EERRCB,
    };
public:
    static ECodeMapType ECodeMap;
public:
    IoRet(int err_code = 0) : ret::Return(err_code) {
        err_code_vec_.push_back(&IoRet::ECodeMap);
    }
    ~IoRet() { };
};

}

#endif
