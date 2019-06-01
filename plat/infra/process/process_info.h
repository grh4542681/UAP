#ifndef __PROCESS_INFO_H__
#define __PROCESS_INFO_H__

#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <errno.h>
#include <map>
#include <vector>

#include "file.h"
#include "report.h"
#include "mempool.h"
#include "thread_info.h"
#include "mutex/thread_rw_lock.h"
#include "socket/sock_pair.h"

#include "process_log.h"
#include "process_return.h"
#include "process_state.h"
#include "process_role.h"
#include "process_id.h"
#include "process_parent.h"
#include "process_child.h"

namespace process::single {

template < typename F > class ProcessSingle;

}

namespace process {
class Process;
class ProcessInfo : public report::VReport {
public:
    friend class mempool::MemPool;
    friend class Process;
    template <typename F> friend class single::ProcessSingle;
public:

    ProcessID& GetPid();
    std::string& GetName();
    std::string& GetRealName();
    std::string& GetRealPath();
    ProcessState& GetProcessState();
    ProcessRole& GetProcessRole();
    std::string& GetProcessPoolName();
    const char* GetCmdLine(unsigned int index);
    ProcessInfo& GetCmdLine(char*** raw_cmdline, unsigned int* raw_cmdline_size);

    ProcessInfo& SetPid(ProcessID&& pid);
    ProcessInfo& SetName(std::string name);
    ProcessInfo& SetRealName();
    ProcessInfo& SetRealPath();
    ProcessInfo& SetCmdLine(int argc, char** argv, char** env);
    ProcessInfo& SetCmdLine(char** raw_cmdline, unsigned int raw_cmdline_size);

    ProcessRet AddThreadInfo(thread::ThreadInfo* thread_info);
    ProcessRet DelThreadInfo(pid_t tid);

    ProcessRet AddParentProcess(ProcessParent& parent);
    ProcessRet AddParentProcess(ProcessParent&& parent);
    ProcessRet DelParentProcess();
    ProcessParent* GetParentProcess();

    ProcessRet AddChildProcess(ProcessChild& child);
    ProcessRet AddChildProcess(ProcessChild&& child);
    ProcessRet DelChildProcess(ProcessID& pid);
    ProcessRet DelChildProcess(ProcessID&& pid);
    ProcessRet DelChildProcess(std::string name);
    ProcessChild* GetChildProcess(ProcessID& pid);
    ProcessChild* GetChildProcess(ProcessID&& pid);
    ProcessRet GetChildProcess(std::string name, std::vector<ProcessChild*> child_vector);

    void Report(file::File& fd, report::ReportMode mode);
    void Report(std::stringstream& ss, report::ReportMode mode);

    static ProcessInfo* getInstance();
    static void setInstance(ProcessInfo* info);


private:
    ProcessInfo();
    ProcessInfo(ProcessInfo& other);
    ~ProcessInfo();
public:

private:
    mempool::MemPool* mempool_;

    // base argement
    ProcessID           pid_;           ///< Process id.
    std::string         name_;          ///< User defined process name.
    std::string         real_path_;     ///< Process exec path.
    std::string         real_name_;     ///< Real process name.
    ProcessState        state_;         ///< Process state.
    ProcessRole         role_;          ///< Process role.
    std::string         pool_name_;     ///< Process belong to which process pool.

    // Command line argument
    char**              raw_cmdline_;       ///< Original command line parameter.
    unsigned int        raw_cmdline_size_;  ///< Size of original command line.
    std::vector<char*>  cmdline_;           ///< Command line arguments vector.
    std::vector<char*>  environ_;           ///< Environment arguments vector.

    // process relationship
    ProcessParent*                      parent_;    ///< Parent process info.
    std::map<ProcessID, ProcessChild*> child_;     ///< Child process info.

    // thread info
    thread::mutex::ThreadRWLock thread_info_rw_lock_;       ///< Mutex lock of thread map.
    std::map<pid_t, thread::ThreadInfo*> thread_info_map_;  ///< Map of all thread in this process.

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
