/*******************************************************
 * Copyright (C) For free.
 * All rights reserved.
 *******************************************************
 * @author   : Ronghua Gao
 * @date     : 2019-04-17 10:46
 * @file     : process_single.h
 * @brief    : Create singal process.
 * @note     : Email - grh4542681@163.com
 * ******************************************************/
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

/**
* @brief - Create singal process.
*
* @tparam [F] - process main function
*/
template < typename F >
class ProcessSingle {
public:
    /**
    * @brief ProcessSingle - Constructor
    *
    * @param [child] - process main function.
    */
    ProcessSingle(F child) {
        mempool_ = mempool::MemPool::getInstance();
        name_.clear();
        child_ = child;
    }

    /**
    * @brief ProcessSingle - Constructor
    *
    * @param [name] - Process name.
    * @param [child] - Process main function.
    */
    ProcessSingle(std::string name, F child) {
        mempool_ = mempool::MemPool::getInstance();
        name_ = name;
        child_ = child;
    }

    ~ProcessSingle() {

    }

    /**
    * @brief SetSigChldCallback - Set the callback if process dead parent process
    *                       will invoke the function.
    *
    * @param [sigchld_callback] - Callback function.
    */
    void SetSigChldCallback(void (*sigchld_callback)(int*)) {
        sigchld_callback_ = sigchld_callback;
    }

    /**
    * @brief Run - Start process.
    *
    * @tparam [Args] - Template Args of main function.
    * @param [args] - args.
    *
    * @returns  ProcessRet.
    */
    template <typename ... Args>
    ProcessRet Run(Args&& ... args) {
        PROCESS_INFO("Starting create process.");
        ProcessRet ret;
        //Create socket pair
        ipc::sock::SockPair pair;
        if (pair.Open() != ipc::IpcRet::SUCCESS) {
            PROCESS_ERROR("SockPair Open error.");
            return ProcessRet::PROCESS_EFIFOPAIR;
        }

        //Reset signal
        signal::ProcessSignalCtrl* psignal = signal::ProcessSignalCtrl::getInstance();
        if ((ret = psignal->UnRegister()) != ProcessRet::SUCCESS) {
            pair.Close();
            PROCESS_ERROR("Reset signal error.");
            return ret;
        }

        ProcessInfo* parent = ProcessInfo::getInstance();

        pid_t pid = fork();
        if (pid < 0) {
            pair.Close();
            psignal->Revert();
            PROCESS_ERROR("Fork error.");
            return ProcessRet::PROCESS_EFORK;
        } else if (pid == 0) {
            //destory parent mempool

            ProcessInfo::pInstance = NULL;
            ProcessInfo* child = ProcessInfo::getInstance();
            child->pair_ = pair;
            child->pair_.SetAutoClose(true);
            child->raw_cmdline_ = parent->raw_cmdline_;
            child->raw_cmdline_size_ = parent->raw_cmdline_size_;
            child->cmdline_ = parent->cmdline_;
            child->environ_ = parent->environ_;
            child->sigchld_callback_ = sigchld_callback_;
            if (!name_.empty()) {
                Process::SetProcName(name_);
            }
            Process::GetProcName(child->process_name_);

            PROCESS_INFO("Execute child main function.");
            _run_main(std::forward<Args>(args)...);
            exit(0);
        } else {
            psignal->Revert();
            ProcessInfo child;
            child.pid_ = pid;
            child.ppid_ = parent->pid_;
            child.pair_ = pair;
            child.pair_.SetAutoClose(true);
            child.sigchld_callback_ = sigchld_callback_;

            PROCESS_INFO("Register child [%d] into current process.", pid);
            return parent->AddChildProcessInfo(child);
        }
        return ProcessRet::SUCCESS;
    }

private:
    mempool::MemPool* mempool_;         ///< Mempool pointer.
    std::string name_;                  ///< Process Name.
    F child_;                           ///< Process main function.
    void (*sigchld_callback_)(int*);    ///< Process dead callback for parent SIGCHLD.

    template <typename ... Args>
    ProcessRet _run_main(Args&& ... args) {
        child_(std::forward<Args>(args)...);
        return ProcessRet::SUCCESS;
    }
};

/**
* @brief - ProcessSingle template string type exception.
*/
template < >
class ProcessSingle<std::string> {
public:
    /**
    * @brief ProcessSingle - Constructor
    *
    * @param [child] - Process execute path.
    */
    ProcessSingle(std::string child) {
        mempool_ = mempool::MemPool::getInstance();
        child_ = child;
    }

    /**
    * @brief ProcessSingle - Constructor
    *
    * @param [name] - Process name.
    * @param [child] - Process execute path.
    */
    ProcessSingle(std::string name, std::string child) {
        mempool_ = mempool::MemPool::getInstance();
        name_ = name;
        child_ = child;
    }

    ~ProcessSingle() {

    }

    /**
    * @brief SetSigChldCallback - Set the callback if process dead parent process
    *                       will invoke the function.
    *
    * @param [sigchld_callback] - Callback function.
    */
    void SetSigChldCallback(void (*sigchld_callback)(int*)) {
        sigchld_callback_ = sigchld_callback;
    }

    /**
    * @brief Run - Start process.
    *
    * @returns  ProcessRet.
    */
    ProcessRet Run() {
        //Reset signal
        ProcessRet ret;
        signal::ProcessSignalCtrl* psignal = signal::ProcessSignalCtrl::getInstance();
        if ((ret = psignal->UnRegister()) != ProcessRet::SUCCESS) {
            PROCESS_ERROR("Reset signal error.");
            return ret;
        }

        pid_t pid = fork();
        if (pid < 0) {
            psignal->Revert();
            PROCESS_ERROR("Fork error.");
            return ProcessRet::PROCESS_EFORK;
        } else if (pid == 0) {
            PROCESS_INFO("Execute child [%s].", child_.c_str());
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

            PROCESS_INFO("Register child [%d] into current process.", pid);
            return parent->AddChildProcessInfo(child_process_info);
        }
        return ProcessRet::SUCCESS;
    }

private:
    mempool::MemPool* mempool_;         ///< Mempool pointer.
    std::string name_;                  ///< Process Name.
    std::string child_;                 ///< Process execute path.
    void (*sigchld_callback_)(int*);    ///< Process dead callback for parent SIGCHLD.
};

};

#endif
