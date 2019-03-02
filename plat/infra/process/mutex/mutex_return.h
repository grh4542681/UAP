#ifndef __MUTEX_RETURN_H__
#define __MUTEX_RETURN_H__

namespace infra::process::mutex {

typedef enum class _MutexRet: int {
    SUCCESS = 0x00,
    ERROR = 0xFF,

    UNINIT = 0x01,
} MutexRet;

//typedef enum class _MutexRet MutexRet;

} // namespace pub

#endif
