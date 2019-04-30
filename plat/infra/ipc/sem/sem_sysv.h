#ifndef __SEM_SYSV_H___
#define __SEM_SYSV_H___

#include <sys/types.h>
#include <errno.h>

#include "ipc_return.h"
#include "sem.h"

namespace ipc::sem {

/**
* @brief - System V semphore set.
*/
class SemSysV : public Sem {
public:
    SemSysV();
    SemSysV(std::string path);
    ~SemSysV();

    IpcRet Create(size_t semnum, mode_t mode);
    IpcRet Destroy();
    IpcRet Open(IpcMode mode);
    IpcRet Close();

protected:
    IpcRet _p(size_t sem_index, unsigned int num, util::time::Time* overtime);
    IpcRet _v(size_t sem_index, unsigned int num);

private:
    union semun {
        int              val;    /* Value for SETVAL */
        struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
        unsigned short  *array;  /* Array for GETALL, SETALL */
        struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                       (Linux-specific) */
    };

    int semid_; ///< Semaphore set id.
    key_t key_; ///< Semaphore set key.

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

};

} // namespace ipc

#endif
