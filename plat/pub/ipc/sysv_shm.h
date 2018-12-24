#ifndef __SYSV_SHM_H__
#define __SYSV_SHM_H__

#include <sys/types.h>
#include <sys/shm.h>

#include "ipc_log.h"
#include "ipc_return.h"
#include "rm_return.h""
#include "rm_controllable.h"

namespace ipc {

class SysVShm : public rm::RMControllable{
public:
    SysVShm(key_t key, size_t size);
    SysVShm(key_t key, size_t size, mode_t mode);

    ~SysVShm();

    rm::RmRet create();
    rm::RmRet destroy();
    IpcRet At();
    IpcRet Dt();

    IpcRet Write(void* data, void* datalen);
    IpcRet Write(void* pstart, void* data, void* datalen);
    IpcRet Read(void* data, void* datalen);
    IpcRet Read(void* pstart, void* data, void* datalen);
private:
    int shmid_;
    key_t key_;
    size_t size;
    mode_t mode_;
    int init_flag_;

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
    
    IpcRet _write(void* pstart, void* data, unsigned int datalen);
    IpcRet _read(void* pstart, void* data, unsigned int datalen);
};

}//namespace ipc end

#endif
