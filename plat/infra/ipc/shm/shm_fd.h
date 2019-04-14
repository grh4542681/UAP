#ifndef __SHM_FD_H__
#define __SHM_FD_H__

#include "ipc_return.h"

namespace ipc::shm {
    
class ShmFD {
public:
    ShmFD();
    ShmFD(int fd);
    ShmFD(const ShmFD& other);
    ~ShmFD();

    void Close();

    IpcRet Seek(int offset);
    int Read(void* data, unsigned int datalen);
    int Write(const void* data, unsigned int datalen);

    ShmFD& operator= (const ShmFD& other);
private:
    int fd_;
};

}
#endif
