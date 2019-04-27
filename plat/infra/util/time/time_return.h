#ifndef __TIME_RETURN_H__
#define __TIME_RETURN_H__

namespace util::time {

enum class TimeRet: int {
//common return val
    SUCCESS = 0,
    ERROR = -999,
    EMALLOC,
    EINIT,
    ETIMEOUT,
    EBADARGS,
    EUNKOWNERRNO,
    ESUBCLASS,

//time
    ETIMEGET,

};

}

#endif
