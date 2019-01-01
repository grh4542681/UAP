#ifndef __SYSV_IPC_RESOURCE_CTRL__
#define __SYSV_IPC_RESOURCE_CTRL__

#include "rm_controllable.h"

namespace rm {

class IpcCtrlElement : public RmControlElement{
    key_t ipc_key;
    
};

class IpcTransElement : public RmTransferElement{
    ControlType ctype;
};

class IpcCtrlApi : public RmControlApi {
    RmRet Create(RmTransferElement*);
    RmRet Delete(RmTransferElement*);
    RmRet Update(RmTransferElement*);
    RmRet Select(RmTransferElement*);
    RmRet Show(RmTransferElement*);
};

} //namespace end

#endif