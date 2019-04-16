#include <sys/prctl.h>

#include "process.h"

namespace process {


ProcessRet Process::SetProcName(std::string name)
{
    ProcessInfo* info = ProcessInfo::getInstance();
    if (!info || !info->raw_cmdline_) {
        return ProcessRet::EBADARGS;
    }
    if (name.size() >= info->raw_cmdline_size_) {
        name.resize(info->raw_cmdline_size_);
    }
    memcpy(info->raw_cmdline_[0], name.c_str(), name.size());
    memset(info->raw_cmdline_[0] + name.size(), 0, strlen(info->raw_cmdline_[0]) - name.size());
    prctl(PR_SET_NAME, name.c_str());
    return ProcessRet::SUCCESS;
}

ProcessRet Process::SendToParent(char* msg, unsigned int* msglen, util::time::Time* overtime)
{
    ProcessInfo* self_info = ProcessInfo::getInstance();
    return ProcessRet::SUCCESS;
}


ProcessRet Process::RecvFromParent(char* msg, unsigned int* msglen, util::time::Time* overtime)
{
    ProcessInfo* self_info = ProcessInfo::getInstance();
    return ProcessRet::SUCCESS;
}

}
