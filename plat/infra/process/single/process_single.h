#ifndef _PROCESS_SINGLE_H__
#define _PROCESS_SINGLE_H__

#include <unistd.h>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <string>
#include <functional>

#include "mempool.h"

#include "process_info.h"

namespace process::single {

template < typename F >
class ProcessSingle {
public:
    ProcessSingle(F child) {
        run_flag_ = false;
        mempool_ = mempool::MemPool::getInstance();
        child_ = child;
    }

    ~ProcessSingle() {

    }

    template <typename ... Args>
    ProcessRet Run(Args&& ... args) {

        ipc::sock::SockPair pair;
        if (pair.Open() != ipc::IpcRet::SUCCESS) {
            return ProcessRet::PROCESS_EFIFOPAIR;
        }
        pid_t pid = fork();
        if (pid < 0) {
            pair.Close();
            return ProcessRet::PROCESS_EFORK;
        } else if (pid == 0) {
            ProcessInfo* process_info = ProcessInfo::getInstance();
            process_info->pair_ = pair;
            process_info->pair_.SetAutoClose(true);
            _run_main(std::forward<Args>(args)...);
            exit(0);
        } else {
            ProcessInfo* parent = ProcessInfo::getInstance();
            ProcessInfo child_process_info;
            child_process_info.pid_ = pid;
            child_process_info.ppid_ = parent->pid_;
            child_process_info.pair_ = pair;
            child_process_info.pair_.SetAutoClose(true);
            run_flag_ = true;

            return parent->AddChildProcessInfo(child_process_info);
        }
        return ProcessRet::SUCCESS;
    }

private:
    mempool::MemPool* mempool_;
    bool run_flag_;
    ProcessInfo* process_info_;
    F child_;

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
        run_flag_ = false;
        mempool_ = mempool::MemPool::getInstance();
        child_ = child;
    }

    ~ProcessSingle() {

    }

    template <typename ... Args>
    ProcessRet Run(Args&& ... args) {
        ipc::sock::SockPair pair;
        if (pair.Open() != ipc::IpcRet::SUCCESS) {
            return ProcessRet::PROCESS_EFIFOPAIR;
        }
        pid_t pid = fork();
        if (pid < 0) {
            pair.Close();
            return ProcessRet::PROCESS_EFORK;
        } else if (pid == 0) {

        } else {
            ProcessInfo* parent = ProcessInfo::getInstance();
            ProcessInfo child_process_info;
            child_process_info.pid_ = pid;
            child_process_info.ppid_ = parent->pid_;
            child_process_info.pair_ = pair;
            child_process_info.pair_.SetAutoClose(true);
            run_flag_ = true;

            return parent->AddChildProcessInfo(child_process_info);
        }
        return ProcessRet::SUCCESS;
    }

private:
    mempool::MemPool* mempool_;
    bool run_flag_;
    ProcessInfo* process_info_;
    std::string child_;
};

};

#endif
