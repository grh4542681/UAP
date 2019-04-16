#ifndef _PROCESS_SINGLE_H__
#define _PROCESS_SINGLE_H__

#include <unistd.h>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <string>
#include <functional>

#include "mempool.h"

#include "process.h"
#include "process_info.h"
#include "signal/process_signal_ctrl.h"

namespace process::single {

template < typename F >
class ProcessSingle {
public:
    ProcessSingle(F child) {
        mempool_ = mempool::MemPool::getInstance();
        name_.clear();
        child_ = child;
    }

    ProcessSingle(std::string name, F child) {
        mempool_ = mempool::MemPool::getInstance();
        name_ = name;
        child_ = child;
    }

    ~ProcessSingle() {

    }

    void SetSigChldCallback(void (*sigchld_callback)(int*)) {
        sigchld_callback_ = sigchld_callback;
    }

    template <typename ... Args>
    ProcessRet Run(Args&& ... args) {
        ProcessRet ret;
        //Create socket pair
        ipc::sock::SockPair pair;
        if (pair.Open() != ipc::IpcRet::SUCCESS) {
            return ProcessRet::PROCESS_EFIFOPAIR;
        }

        //Reset signal
        signal::ProcessSignalCtrl* psignal = signal::ProcessSignalCtrl::getInstance();
        if ((ret = psignal->UnRegister()) != ProcessRet::SUCCESS) {
            pair.Close();
            return ret;
        }

        ProcessInfo* parent = ProcessInfo::getInstance();

        pid_t pid = fork();
        if (pid < 0) {
            pair.Close();
            psignal->Revert();
            return ProcessRet::PROCESS_EFORK;
        } else if (pid == 0) {
            ProcessInfo* process_info = ProcessInfo::getInstance();
            process_info->pair_ = pair;
            process_info->pair_.SetAutoClose(true);
            process_info->raw_cmdline_ = parent->raw_cmdline_;
            process_info->raw_cmdline_size_ = parent->raw_cmdline_size_;
            process_info->cmdline_ = parent->cmdline_;
            process_info->environ_ = parent->environ_;
            process_info->sigchld_callback_ = sigchld_callback_;
            if (!name_.empty()) {
                Process::SetProcName(name_);
            }
            _run_main(std::forward<Args>(args)...);
            exit(0);
        } else {
            psignal->Revert();
            ProcessInfo child_process_info;
            child_process_info.pid_ = pid;
            child_process_info.ppid_ = parent->pid_;
            child_process_info.pair_ = pair;
            child_process_info.pair_.SetAutoClose(true);
            child_process_info.sigchld_callback_ = sigchld_callback_;

            return parent->AddChildProcessInfo(child_process_info);
        }
        return ProcessRet::SUCCESS;
    }

private:
    mempool::MemPool* mempool_;
    std::string name_;
    F child_;
    void (*sigchld_callback_)(int*);

    template <typename ... Args>
    ProcessRet _run_main(Args&& ... args) {
        child_(std::forward<Args>(args)...);
        return ProcessRet::SUCCESS;
    }
};

template < >
class ProcessSingle<std::string> {
public:
    ProcessSingle(std::string child) {
        mempool_ = mempool::MemPool::getInstance();
        child_ = child;
    }

    ~ProcessSingle() {

    }

    template <typename ... Args>
    ProcessRet Run(Args&& ... args) {
        //Reset signal
        ProcessRet ret;
        signal::ProcessSignalCtrl* psignal = signal::ProcessSignalCtrl::getInstance();
        if ((ret = psignal->UnRegister()) != ProcessRet::SUCCESS) {
            return ret;
        }

        pid_t pid = fork();
        if (pid < 0) {
            psignal->Revert();
            return ProcessRet::PROCESS_EFORK;
        } else if (pid == 0) {
            if (execl(child_.c_str(), child_.c_str(), 0) < 0) {
                PROCESS_ERROR("Exec bin [%s] errno [%d].", child_.c_str(), errno);
                exit(-1);
            }
        } else {
            psignal->Revert();
            ProcessInfo* parent = ProcessInfo::getInstance();
            ProcessInfo child_process_info;
            child_process_info.pid_ = pid;
            child_process_info.ppid_ = parent->pid_;
            child_process_info.pair_.SetAutoClose(true);

            return parent->AddChildProcessInfo(child_process_info);
        }
        return ProcessRet::SUCCESS;
    }

private:
    mempool::MemPool* mempool_;
    std::string child_;
};

};

#endif
