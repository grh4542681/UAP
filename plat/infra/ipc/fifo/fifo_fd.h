#ifndef __FIFO_FD_H__
#define __FIFO_FD_H__

#include "ipc_fd.h"

namespace ipc::fifo {
    
class FifoFD : public IpcFD {
public:
    FifoFD();
    FifoFD(int fd);
    FifoFD(const FifoFD& other);
    ~FifoFD();

    void Close();

    int Read(void* data, unsigned int datalen);
    int Write(const void* data, unsigned int datalen);

    FifoFD& operator= (const FifoFD& other);
private:
    int fd_;
};

}
#endif
