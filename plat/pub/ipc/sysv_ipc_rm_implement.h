#ifndef __SYSV_IPC_RESOURCE_CTRL__
#define __SYSV_IPC_RESOURCE_CTRL__

#include "rm_return.h"
#include "rm_controllable.h"

namespace rm {

class SysVIpcRmCtrlElement : public RmControlElement{
    key_t ipc_key;
    
};

class SysVIpcRmTransElement : public RmTransferElement{
    ControlType ctype;
};

class SysVIpcRmCtrlApi : public RmControlApi {
public:
    SysVIpcRmCtrlApi();
    ~SysVIpcRmCtrlApi();

    RmRet Create(RmTransferElement*);
    RmRet Delete(RmTransferElement*);
    RmRet Update(RmTransferElement*);
    RmRet Select(RmTransferElement*);
    RmRet Show(RmTransferElement*);
};

} //namespace end

#endif
