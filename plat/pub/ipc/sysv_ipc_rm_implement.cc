#include "sysv_ipc_rm_implement.h"

#include "rm_common.h"
#include "rm_return.h"
#include "rm_controllable.h"

namespace rm {

SysVIpcRmCtrlApi::SysVIpcRmCtrlApi()
{
    this->type_ = ResourceType::SYSV_IPC_KEY;
}

SysVIpcRmCtrlApi::~SysVIpcRmCtrlApi()
{

}

RmRet SysVIpcRmCtrlApi::Create(RmTransferElement*)
{

}

RmRet SysVIpcRmCtrlApi::Delete(RmTransferElement*)
{

}

RmRet SysVIpcRmCtrlApi::Update(RmTransferElement*)
{

}

RmRet SysVIpcRmCtrlApi::Select(RmTransferElement*)
{

}

RmRet SysVIpcRmCtrlApi::Show(RmTransferElement*)
{

}

//common entry function
RmRet ResourceCtrlInit(RmControlApi* api)
{

}

} //namespace end
