#ifndef __IPC_FD_H__
#define __IPC_FD_H__

#include "ipc_fd_type.h"

namespace ipc {

class IpcFD {
    IpcFDType fd_type_;
    IpcFD();
    virtual ~IpcFD();

    virtual int Read(void* data, unsigned int datalen) { return 0; };
    virtual int Write(const void* data, unsigned int datalen) { return 0; };
};

}

#endif