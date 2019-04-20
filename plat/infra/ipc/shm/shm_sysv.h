#ifndef __SHM_SYSV_H__
#define __SHM_SYSV_H__

#include <sys/types.h>
#include <sys/shm.h>

#include "ipc_log.h"
#include "ipc_return.h"

namespace ipc {

class ShmSysV {
public:
    ShmSysV(key_t key, size_t size);
    ShmSysV(key_t key, size_t size, mode_t mode);
    ~ShmSysV();
    
    IpcRet At();
    IpcRet Dt();

    IpcRet Write(void* data, void* datalen);
    IpcRet Write(void* pstart, void* data, void* datalen);
    IpcRet Read(void* data, void* datalen);
    IpcRet Read(void* pstart, void* data, void* datalen);

    IpcRet Create();
    IpcRet Destory();

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
    
    IpcRet _write(void* pstart, void* data, unsigned int datalen);
    IpcRet _read(void* pstart, void* data, unsigned int datalen);
};

}//namespace ipc end

#endif
