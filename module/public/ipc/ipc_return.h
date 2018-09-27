#ifndef __MUTEX_RETURN_H__
#define __MUTEX_RETURN_H__

namespace base{

typedef enum class _IpcRet: int {
    SUCCESS = 0x00,
    ERROR,

//sem return val
    SEM_EEXIST,
    SEM_EACCES,
    SEM_EINVAL,
    SEM_ENOENT,
    SEM_ENOMEM,
    SEM_ENOSPC,
} IpcRet;

} // namespace base

#endif
