#ifndef __SYSV_IPC_RM_CTRL_H__
#define __SYSV_IPC_RM_CTRL_H__

#include "ipc_return.h"

namespace ipc {

class SysVIpcRmCtrl {
public:
    SysVIpcRmCtrl();
    ~SysVIpcRmCtrl();

    IpcRet Create();
    IpcRet Update();
    IpcRet Delete();
};

}//namespace end

#endif
