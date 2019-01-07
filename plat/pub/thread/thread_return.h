#ifndef __THREAD_RETURN_H__
#define __THREAD_RETURN_H__

#include <errno.h>

namespace thread{

typedef enum class _ThreadRet: int {
//common return val
    SUCCESS = 0,
    ERROR = -999,
    EMALLOC,
    EINIT,
    EBADARGS,
    ETIMEOUT,
    EUNKOWNERRNO,

} ThreadRet;

} // namespace THREAD

#endif
