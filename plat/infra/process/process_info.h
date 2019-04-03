#ifndef __PROCESS_INFO_H__
#define __PROCESS_INFO_H__

#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <errno.h>
#include <map>

#include "file.h"
#include "report.h"
#include "process_log.h"
#include "process_return.h"

#include "thread_info.h"

namespace process {

class ProcessInfo : public report::VReport {
public:
    pid_t GetPid();
    pid_t GetPPid();
    std::string& GetName();
    std::string& GetProcessName();

    ProcessRet AddThreadInfo(thread::ThreadInfo* thread_info);
    ProcessRet DelThreadInfo(pid_t tid);

    void Report(file::File& fd, report::ReportMode mode);
    void Report(std::stringstream& ss, report::ReportMode mode);

    static ProcessInfo* getInstance();
    static ProcessRet GetCurrProcessName(std::string& name);

private:
    ProcessInfo();
    ~ProcessInfo();

private:
    pid_t pid_;
    pid_t ppid_;
    std::string process_name_;
    std::string name_;

    std::map<pid_t, thread::ThreadInfo*> thread_info_map_;

    static ProcessInfo* pInstance;

public:
    static ProcessRet _error2ret(int ierrno) {
        switch (ierrno) {
            case 0:
                return ProcessRet::SUCCESS;
            case EACCES:
                return ProcessRet::PROCESS_EACCES;
            case EFAULT:
                return ProcessRet::PROCESS_EFAULT;
            case EINVAL:
                return ProcessRet::PROCESS_EINVAL;
            case EIO:
                return ProcessRet::PROCESS_EIO;
            case ELOOP:
                return ProcessRet::PROCESS_ELOOP;
            case ENAMETOOLONG:
                return ProcessRet::PROCESS_ENAMETOOLONG;
            case ENOENT:
                return ProcessRet::PROCESS_ENOENT;
            case ENOMEM:
                return ProcessRet::PROCESS_ENOMEM;
            case ENOTDIR:
                return ProcessRet::PROCESS_ENOTDIR;
            default:
                PROCESS_ERROR("Unknow errno[%d]", ierrno);
                return ProcessRet::EUNKOWNERRNO;
        }
    }
};

};

#endif
