#ifndef __THREAD_RETURN_H__
#define __THREAD_RETURN_H__

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
