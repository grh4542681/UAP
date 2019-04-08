#ifndef __IPC_FD_TYPE_H__
#define __IPC_FD_TYPE_H__

namespace ipc {

enum class IpcFDType {
    NONE,
    FIFO,
    SYSV_MSG,
    SYSV_SEM,
    SYSV_SHM,
};

}

#endif
