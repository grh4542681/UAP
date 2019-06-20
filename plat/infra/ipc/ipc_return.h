#ifndef __IPC_RETURN_H__
#define __IPC_RETURN_H__

namespace ipc{

enum class IpcRet: int {
//common return val
    SUCCESS = 0x00,
    ERROR,
    EBADARGS,
    EMALLOC,
    EINIT,
    ETIMEOUT,
    ESUBCLASS,

    EUNKOWNERRNO,

// fifo return val
    FIFO_ESOCKPAIR,

// shm return val
    SHM_EMODE,
    SHM_ECREATED,

    SHM_EACCES,
    SHM_EEXIST,
    SHM_EINVAL,
    SHM_ENFILE,
    SHM_ENOENT,
    SHM_ENOMEM,
    SHM_ENOSPC,
    SHM_EPERM,

// sem return val
    SEM_EMODE,
    SEM_ENOTFOUND,

    SEM_EEXIST,
    SEM_EACCES,
    SEM_EINVAL,
    SEM_ENOENT,
    SEM_ENOMEM,
    SEM_ENOSPC,
    SEM_ETIMEOUT,

// sem rw lock
    SEM_ELOCKED,
};

} // namespace ipc

#endif
