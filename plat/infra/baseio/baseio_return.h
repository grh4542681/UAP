#ifndef __BASEIO_RETURN_H__
#define __BASEIO_RETURN_H__

namespace baseio {

enum class BaseIORet: int {
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
