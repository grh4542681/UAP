#ifndef __IO_RETURN_H__
#define __IO_RETURN_H__

#include "return.h"

namespace io {

class IoRet : public ret::Return {
public:
    IoRet(int err_code) : ret::Return(err_code) { }
    ~IoRet();

};

}

#endif
