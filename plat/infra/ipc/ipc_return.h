#ifndef __IPC_RETURN_H__
#define __IPC_RETURN_H__

namespace ipc{

typedef enum class _IpcRet: int {
//common return val
    SUCCESS = 0x00,
    ERROR,
    EMALLOC,
    EINIT,
    ETIMEOUT,

    EUNKOWNERRNO,

// fifo return val
    FIFO_ESOCKPAIR,

//sem system return val
    SEM_EEXIST,
    SEM_EACCES,
    SEM_EINVAL,
    SEM_ENOENT,
    SEM_ENOMEM,
    SEM_ENOSPC,
} IpcRet;

} // namespace ipc

#endif
