#include "process.h"

namespace process {

ProcessRet Process::SetProcName(std::string name)
{
    ProcessInfo* self = ProcessInfo::getInstance();
    return SetProcName(self, name);
}

ProcessRet Process::SetProcName(ProcessInfo* info, std::string name)
{
    return ProcessRet::SUCCESS;
}

ProcessRet Process::SendToParent(char* msg, unsigned int* msglen, util::time::Time* overtime)
{
    ProcessInfo* self_info = ProcessInfo::getInstance();
    return SendToParent(self_info, msg, msglen, overtime);
}

ProcessRet Process::SendToParent(ProcessInfo* info, char* msg, unsigned int* msglen, util::time::Time* overtime)
{
    return ProcessRet::SUCCESS;
}

ProcessRet Process::RecvFromParent(char* msg, unsigned int* msglen, util::time::Time* overtime)
{
    ProcessInfo* self_info = ProcessInfo::getInstance();
    return RecvFromParent(self_info, msg, msglen, overtime);
}

ProcessRet Process::RecvFromParent(ProcessInfo* info, char* msg, unsigned int* msglen, util::time::Time* overtime)
{
    return ProcessRet::SUCCESS;
}


}
