#ifndef __FIFO_FD_H__
#define __FIFO_FD_H__

#include "ipc_fd.h"

namespace ipc::fifo {
    
class FifoFD : public IpcFD {
public:
    FifoFD(int fd);
    ~FifoFD();

    int Read(void* data, unsigned int datalen);
    int Write(const void* data, unsigned int datalen);
};

}
#endif