#ifndef __MUTEX_RETURN__
#define __MUTEX_RETURN__

namespace base{

typedef enum class _MutexRet: int {
    SUCCESS = 0x00,
    ERROR = 0xFF,
} MutexRet;

//typedef enum class _MutexRet MutexRet;

} // namespace base

#endif
