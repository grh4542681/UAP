#include <string.h>

#include "process_info.h"

#define MAX_PROCCESS_NAME_LEN (1024)

namespace process {

ProcessInfo* ProcessInfo::pInstance = NULL;

ProcessInfo::ProcessInfo()
{
    pid_ = getpid();
    ppid_ = getppid();
    if (GetCurrProcessName(process_name_) != ProcessRet::SUCCESS) {
        PROCESS_ERROR("Get process name error");
        process_name_.erase();
    }
    char name[MAX_PROCCESS_NAME_LEN];
    memset(name, 0x00, sizeof(name));
    sprintf(name, "%s_%lu", process_name_, pid_);
    name_.assign(name);
}

ProcessInfo::~ProcessInfo()
{

}

ProcessInfo* ProcessInfo::getInstance()
{
    if (!pInstance) {
        pInstance = new ProcessInfo();
    }
    return pInstance;
}

ProcessRet ProcessInfo::GetCurrProcessName(std::string& name)
{
    char process_path[MAX_PROCCESS_NAME_LEN];
    memset(process_path, 0x00, sizeof(process_path));
    if (readlink("proc/self/exe", process_path, sizeof(process_path)-1) < 0) {
        int tmperrno = errno;
        PROCESS_ERROR("Get process name error");
        return _error2ret(tmperrno);
    }
    name.assign(process_path);
    return ProcessRet::SUCCESS;
}

}
