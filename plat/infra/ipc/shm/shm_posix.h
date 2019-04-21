#ifndef __SHM_POSIX_H__
#define __SHM_POSIX_H__
#include "ipc_log.h"
#include "ipc_return.h"
#include "shm.h"

namespace ipc::shm {

class ShmPosix : public Shm {
public:
    ShmPosix(std::string path);
    ShmPosix();
    ~ShmPosix();

    IpcRet Create(mode_t mode, size_t size);
    IpcRet Destroy();
    IpcRet Open(ShmMode mode);
    IpcRet Close();
    IpcRet Sync();

private:
    int fd_;

    ShmPosix(const ShmPosix& other);

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
