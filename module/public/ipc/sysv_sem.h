#ifndef __POSIX_SEM__
#define __POSIX_SEM__

#include <sys/types.h>

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
    int semid;
    key_t key;
    int semnum;
    mode_t mode;
    unsigned short semval;

    IpcRet Create();
    IpcRet Destroy();
    IpcRet Getid();
};

} // namespace base

#endif
