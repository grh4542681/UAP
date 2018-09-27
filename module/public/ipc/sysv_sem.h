#ifndef __POSIX_SEM__
#define __POSIX_SEM__

#include <sys/types.h>
#include <errno.h>

#include "ipc_return.h"

namespace base {

class SysVSem{
public:
    SysVSem(key_t key, unsigned int semnum, mode_t mode, unsigned short semval);
    ~SysVSem();

    IpcRet Grab(unsigned int timeout);
    IpcRet Grab(unsigned int semnum, unsigned int timeout);
    IpcRet GrabMasksig(unsigned int timeout);
    IpcRet GrabMasksig(unsigned int semnum, unsigned int timeout);
    IpcRet GrabNonblock();
    IpcRet GrabNonblock(unsigned int semnum);

    IpcRet Free();

private:
    typedef union _semun {
        int              val_;    // Value for SETVAL
        struct semid_ds *ds_buf_;    // Buffer for IPC_STAT, IPC_SET
        unsigned short  *array_;  // Array for GETALL, SETALL
        struct seminfo  *info_buf_;    // Buffer for IPC_INFO(Linux-specific)
    }SemUn;

    int init_flag_;
    int semid_;
    key_t key_;
    int semnum_;
    mode_t mode_;
    unsigned short semval_;

    IpcRet _errno2ret(int ierrno){
        switch (ierrno) {
            case EEXIST:
                return IpcRet::SEM_EEXIST;
            case EACCES:
                return IpcRet::SEM_EACCES;
            case EINVAL:
                return IpcRet::SEM_EINVAL;
            case ENOENT:
                return IpcRet::SEM_ENOENT;
            case ENOMEM:
                return IpcRet::SEM_ENOMEM;
            case ENOSPC:
                return IpcRet::SEM_ENOSPC;
            default:
                return IpcRet::ERROR;
        }
    }

    IpcRet _create();
    IpcRet _destroy();
    IpcRet _getid();
};

} // namespace base

#endif
