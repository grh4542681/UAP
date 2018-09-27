#ifndef __MUTEX_RETURN_H__
#define __MUTEX_RETURN_H__

namespace base{

typedef enum class _MutexRet: int {
    SUCCESS = 0x00,
    ERROR = 0xFF,
} MutexRet;

//typedef enum class _MutexRet MutexRet;

} // namespace base

#endif
