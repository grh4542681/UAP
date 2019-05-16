#ifndef __SEM_POSIX_H__
#define __SEM_POSIX_H__

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#include <map>
#include <string>

#include "sem.h"

namespace ipc::sem {

class SemPosix : public Sem {
public:
    SemPosix();
    SemPosix(std::string path);
    ~SemPosix();

    bool IsExist();
    IpcRet Create(size_t semnum, mode_t mode);
    IpcRet Destroy();
    IpcRet Open(IpcMode mode);
    IpcRet Close();

protected:
    IpcRet _p(size_t sem_index, util::time::Time* overtime);
    IpcRet _v(size_t sem_index);

private:
    std::map<std::string, sem_t*> semset_;

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

}

#endif
