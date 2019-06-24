#ifndef __IO_RETURN_H__
#define __IO_RETURN_H__

namespace io {

enum class IoRet: int {

//common return val
    SUCCESS = 0x00,
    ERROR,
    EBADARGS,
    EMALLOC,
    EINIT,
    ETIMEOUT,
    ESUBCLASS,

    EUNKOWNERRNO,
};

}

#endif
