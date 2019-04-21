#ifndef __SHM_SYSV_H__
#define __SHM_SYSV_H__

#include <sys/types.h>
#include <sys/shm.h>

#include "ipc_log.h"
#include "ipc_return.h"
#include "shm.h"
#include "shm_mode.h"

namespace ipc {

class ShmSysV : public Shm{
public:
    ShmSysV(std::string path);
    ShmSysV();
    ~ShmSysV();

    IpcRet Create(size_t size);
    IpcRet Destroy();
    IpcRet Open(ShmMode mode);
    IpcRet Close();

private:
    int shmid_;

    static IpcRet _errno2ret(int ierrno)
    {   
        switch (ierrno) {
            case 0:
                return IpcRet::SUCCESS;
            default:
                return IpcRet::EUNKOWNERRNO;
        }   
    }   

    static int _ret2errno(IpcRet ret)
    {   
        switch (ret) {
            case IpcRet::SUCCESS:
            default:
                return (-1);
        }   
    }
    
};

}//namespace ipc end

#endif
