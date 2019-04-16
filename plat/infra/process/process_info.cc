#include <string.h>

#include "process_info.h"

#define MAX_PROCCESS_NAME_LEN (1024)

namespace process {

ProcessInfo* ProcessInfo::pInstance = NULL;

ProcessInfo::ProcessInfo()
{
    mempool_ = mempool::MemPool::getInstance();
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
    raw_cmdline_ = NULL;
    raw_cmdline_size_ = 0;
    sigchld_callback_ = NULL;
}

ProcessInfo::ProcessInfo(ProcessInfo& other)
{
    mempool_ = other.mempool_;
    pid_ = other.pid_;
    ppid_ = other.ppid_;
    process_name_ = other.process_name_;
    name_ = other.name_;
    pair_ = other.pair_;

    raw_cmdline_ = other.raw_cmdline_;
    raw_cmdline_size_ = other.raw_cmdline_size_;
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

ProcessInfo& ProcessInfo::SetName(std::string name)
{
    name_ = name;
    return *this;
}

ProcessInfo& ProcessInfo::SetCmdLine(int argc, char** argv, char** env)
{
    int loop = 0;
    char* tmp = NULL;

    // back up command line argv
    if (argv) {
        for (loop = 0; loop < argc; loop++) {
            if (strlen(argv[loop]) >= 0) {
                tmp = (char*)(mempool_->Malloc(strlen(argv[loop]) + 1));
                memset(tmp, 0, strlen(argv[loop]));
                memcpy(tmp, argv[loop], strlen(argv[loop]));
                cmdline_.push_back(tmp);
                raw_cmdline_size_ += strlen(argv[loop]) + 1;
            }
        }
        raw_cmdline_ = argv;
    }

    // back up environ args
    if (env) {
        for (loop = 0; env[loop] != NULL; loop++) {
            if (strlen(env[loop]) >= 0) {
                tmp = (char*)(mempool_->Malloc(strlen(env[loop]) + 1));
                memset(tmp, 0, strlen(env[loop]));
                memcpy(tmp, env[loop], strlen(env[loop]));
                cmdline_.push_back(tmp);
                raw_cmdline_size_ += strlen(env[loop]) + 1;
            }
        }
    }
    return *this;
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

ProcessRet ProcessInfo::AddChildProcessInfo(ProcessInfo& process_info)
{
    auto it = process_info_map_.find(process_info.GetPid());
    if (it != process_info_map_.end()) {
        return ProcessRet::PROCESS_EPROCDUP;
    }
    ProcessInfo* p = mempool_->Malloc<ProcessInfo>(process_info);
    if (!p) {
        return ProcessRet::PROCESS_EMEMORY;
    }
    std::pair<std::map<pid_t, ProcessInfo*>::iterator, bool> ret;
    ret = process_info_map_.insert(std::pair<pid_t, ProcessInfo*>(process_info.GetPid(), p));
    if (ret.second == false) {
        return ProcessRet::PROCESS_EPROCADD;
    }
    p->pair_.SetAutoClose(true);
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessInfo::DelChildProcessInfo(pid_t pid)
{
    auto it = process_info_map_.find(pid);
    if (it == process_info_map_.end()) {
        return ProcessRet::PROCESS_EPROCNOTFOUND;
    }

    process_info_map_.erase(it);
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessInfo::DelChildProcessInfo(ProcessInfo* process_info)
{
    if (!process_info) {
        return ProcessRet::EBADARGS;
    }
    mempool_->Free<ProcessInfo>(process_info);
    return ProcessRet::SUCCESS;
}

ProcessInfo* ProcessInfo::FindChildProcessInfo(pid_t pid)
{
    auto it = process_info_map_.find(pid);
    if (it == process_info_map_.end()) {
        return NULL;
    }
    return it->second;
}

void ProcessInfo::Report(file::File& fd, report::ReportMode mode)
{
    thread_info_rw_lock_.RLock(NULL);
    fd.WriteFmt("pid:%u threadnum:%d processnum:%d\n", pid_, thread_info_map_.size(), process_info_map_.size());
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
