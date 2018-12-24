#ifndef __POSIX_SEM__
#define __POSIX_SEM__

#include <sys/types.h>
#include <errno.h>

#include "ipc_return.h"
#include "rm_return.h"
#include "rm_controllable.h"

namespace ipc {

class SysVSem : public rm::RMControllable{
public:
    SysVSem(key_t key);
    SysVSem(key_t key, unsigned short semnum, mode_t mode, unsigned short semval);
    ~SysVSem();

    static key_t GenKey(const char *pathname, int proj_id);

    IpcRet P();
    IpcRet P(struct timespec* over_time);
    IpcRet P(unsigned short op_num);
    IpcRet P(unsigned short op_num, struct timespec* over_time);
    IpcRet P(unsigned short sem_index, unsigned short op_num, struct timespec* over_time);

    IpcRet V();
    IpcRet V(unsigned short op_num);
    IpcRet V(unsigned short sem_index, unsigned short op_num);

    rm::RmRet create();
    rm::RmRet destory();

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
    unsigned short semnum_;
    mode_t mode_;
    unsigned short semval_;

    static IpcRet _errno2ret(int ierrno)
    {
        switch (ierrno) {
            case 0:
                return IpcRet::SUCCESS;
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
                return IpcRet::EUNKOWNERRNO;
        }
    }

    static int _ret2errno(IpcRet ret)
    {
        switch (ret) {
            case IpcRet::SUCCESS:
                return 0;
            case IpcRet::SEM_EEXIST:
                return EEXIST;
            case IpcRet::SEM_EACCES:
                return EACCES;
            case IpcRet::SEM_EINVAL:
                return EINVAL;
            case IpcRet::SEM_ENOENT:
                return ENOENT;
            case IpcRet::SEM_ENOMEM:
                return ENOMEM;
            case IpcRet::SEM_ENOSPC:
                return ENOSPC;
            default:
                return (-1);
        }
    }

    IpcRet _p(unsigned short sem_index, unsigned short op_num, struct timespec* over_time);
    IpcRet _v(unsigned short sem_index, unsigned short op_num);
};

} // namespace ipc

#endif
