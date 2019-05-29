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

    pid_t GetPid();
    pid_t GetPPid();
    std::string& GetName();
    std::string& GetProcessName();
    std::string& GetProcessPath();
    ProcessState& GetProcessState();
    ProcessRole& GetProcessRole();
    std::string& GetProcessPoolName();
    const char* GetCmdLine(unsigned int index);
    void (*GetSigChldCallback())(int*);

    ProcessInfo& SetPid();
    ProcessInfo& SetPPid();
    ProcessInfo& SetName(std::string name);
    ProcessInfo& SetProcessName();
    ProcessInfo& SetProcessPath();
    ProcessInfo& SetCmdLine(int argc, char** argv, char** env);
    ProcessInfo& SetSigChldCallback(void (*sigchld_callback)(int*));

    ProcessRet AddThreadInfo(thread::ThreadInfo* thread_info);
    ProcessRet DelThreadInfo(pid_t tid);

    ProcessRet AddChildProcessInfo(ProcessInfo& process_info);
    ProcessRet DelChildProcessInfo(pid_t pid);
    ProcessRet DelChildProcessInfo(ProcessInfo* process_info);
    ProcessInfo* FindChildProcessInfo(pid_t pid);

    void Report(file::File& fd, report::ReportMode mode);
    void Report(std::stringstream& ss, report::ReportMode mode);

    static ProcessInfo* getInstance();

private:
    ProcessInfo();
    ProcessInfo(ProcessInfo& other);
    ~ProcessInfo();
public:

private:
    mempool::MemPool* mempool_;

    // base
    pid_t pid_;                 ///< Process id.
    pid_t ppid_;                ///< Parent process id.
    std::string name_;          ///< User defined process name.
    std::string process_path_;  ///< Process exec path.
    std::string process_name_;  ///< Real process name.
    ProcessState state_;        ///< Process state.
    ProcessRole role_;          ///< Process role.
    std::string pool_name_;     ///< Process belong to which process pool.
    ipc::sock::SockPair pair_;  ///< Communication channel between father and child processes.
    void (*sigchld_callback_)(int*);    ///< if process dead, parent will use this func deal with SIGCHLD signal.

    // Command line argument
    char** raw_cmdline_;                ///< Original command line parameter.
    unsigned int raw_cmdline_size_;     ///< Size of original command line.
    std::vector<char*> cmdline_;        ///< Command line arguments vector.
    std::vector<char*> environ_;        ///< Environment arguments vector.

    thread::mutex::ThreadRWLock thread_info_rw_lock_;       ///< Mutex lock of thread map.
    std::map<pid_t, thread::ThreadInfo*> thread_info_map_;  ///< Map of all thread in this process.

    std::map<pid_t, ProcessInfo*> process_info_map_;    ///< Map of all child process in this process.

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
