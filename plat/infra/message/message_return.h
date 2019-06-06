#ifndef __MESSAGE_RETURN_H__
#define __MESSAGE_RETURN_H__

namespace message {

enum class MessageRet: int {
//common return val
    SUCCESS = 0x00,
    ERROR,
    EBADARGS,
    EMALLOC,
    EINIT,
    ETIMEOUT,
    ESUBCLASS,

    EUNKOWNERRNO,

// message stream
    EMSNOSPACE,
    EMSNOMESSG,
    EMSMODE,
};

}

#endif
