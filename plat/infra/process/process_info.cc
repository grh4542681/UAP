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
    sprintf(name, "%s_%d", strrchr(process_name_.c_str(), '/') ? strrchr(process_name_.c_str(), '/') + 1 : "", pid_);
    name_.assign(name);
}

ProcessInfo::~ProcessInfo()
{

}

pid_t ProcessInfo::GetPid()
{
    return pid_;
}

pid_t ProcessInfo::GetPPid()
{
    return ppid_;
}

std::string& ProcessInfo::GetName()
{
    return name_;
}

std::string& ProcessInfo::GetProcessName()
{
    return process_name_;
}

ProcessRet ProcessInfo::AddThreadInfo(thread::ThreadInfo* thread_info)
{
    thread_info_rw_lock_.WLock(NULL);
    auto it = thread_info_map_.find(thread_info->GetTid());
    if (it != thread_info_map_.end()) {
        thread_info_rw_lock_.UnLock();
        return ProcessRet::PROCESS_ETHREADDUP;
    }
    std::pair<std::map<pid_t, thread::ThreadInfo*>::iterator, bool> ret;
    ret = thread_info_map_.insert(std::pair<pid_t, thread::ThreadInfo*>(thread_info->GetTid(), thread_info));
    if (ret.second==false) {
        thread_info_rw_lock_.UnLock();
        return ProcessRet::PROCESS_ETHREADADD;
    }
    thread_info_rw_lock_.UnLock();
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessInfo::DelThreadInfo(pid_t tid)
{
    thread_info_rw_lock_.WLock(NULL);
    thread_info_map_.erase(tid);
    thread_info_rw_lock_.UnLock();
    return ProcessRet::SUCCESS;
}

void ProcessInfo::Report(file::File& fd, report::ReportMode mode)
{
    thread_info_rw_lock_.RLock(NULL);
    fd.WriteFmt("pid:%u threadnum:%d\n", pid_, thread_info_map_.size());
    for (auto it : thread_info_map_) {
        fd.WriteFmt("\ttid:%d\n", it.first);
    }
    thread_info_rw_lock_.UnLock();
}

void ProcessInfo::Report(std::stringstream& ss, report::ReportMode mode)
{

}

//static
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
    if (readlink("/proc/self/exe", process_path, sizeof(process_path)-1) < 0) {
        int tmperrno = errno;
        PROCESS_ERROR("Get process name error[%s]", strerror(tmperrno));
        return _error2ret(tmperrno);
    }
    name.assign(process_path);
    return ProcessRet::SUCCESS;
}

}
