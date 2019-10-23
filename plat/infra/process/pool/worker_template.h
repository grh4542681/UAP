#ifndef _WORKER_TEMPLATE_H__
#define _WORKER_TEMPLATE_H__

#include <unistd.h>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <string>
#include <functional>
#include <tuple>

#include "mempool.h"

#include "process.h"
#include "process_info.h"
#include "signal/process_signal_ctrl.h"

namespace process::pool {

template < typename F >
class WorkerTemplate {
public:
    WorkerTemplate() {

    }
    /**
    * @brief WorkerTemplate - Constructor
    *
    * @param [child] - process main function.
    */
    WorkerTemplate(F child) {
        mempool_ = mempool::MemPool::getInstance();
        name_.clear();
        child_ = child;
        auto_create_sockpair_ = false;
    }

    /**
    * @brief WorkerTemplate - Constructor
    *
    * @param [name] - Process name.
    * @param [child] - Process main function.
    */
    WorkerTemplate(std::string name, F child) {
        mempool_ = mempool::MemPool::getInstance();
        name_ = name;
        child_ = child;
        auto_create_sockpair_ = false;
    }

    ~WorkerTemplate() {

    }

    /**
    * @brief SetDeadCallback - Set the callback if process dead parent process
    *                       will invoke the function.
    *
    * @param [sigchld_callback] - Callback function.
    */
    void SetDeadCallback(void (*dead_callback)(int*)) {
        dead_callback_ = dead_callback;
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
    std::tuple<const ProcessRet, const ProcessID> Run(Args&& ... args) {
        PROCESS_INFO("Starting create worker");
        //Create socket pair
        ipc::sock::SockPair pair;
        if (auto_create_sockpair_) {
            if (pair.Open() != ret::Return::SUCCESS) {
                PROCESS_ERROR("SockPair Open error.");
                return {ProcessRet::PROCESS_EFIFOPAIR, ProcessID(0)};
            }
            pair.SetAutoClose(false);
        }
        ProcessInfo* parent = ProcessInfo::getInstance();
        pid_t pid = fork();
        if (pid < 0) {
            if (auto_create_sockpair_) {
                pair.Close();
            }
            PROCESS_ERROR("Fork error.");
            return {ProcessRet::PROCESS_EFORK, ProcessID(0)};
        } else if (pid == 0) {
            //cache parent process data.
            ProcessParent parent_cache(parent->GetName(), parent->GetPid());
            if (auto_create_sockpair_) {
                pair[1].Close();
                parent_cache.SetFD(pair[0]);
            }

            char** raw_cmdline = NULL;
            unsigned int raw_cmdline_size = 0;
            parent->GetCmdLine(&raw_cmdline, &raw_cmdline_size);
 
            //destory parent mempool
            mempool::MemPool::freeInstance();
            ProcessInfo::setInstance(NULL);

            ProcessInfo* child = ProcessInfo::getInstance();
            child->SetName(name_);
            child->SetCmdLine(raw_cmdline, raw_cmdline_size);
            if (!name_.empty()) {
                Process::SetProcName(name_);
            }
            child->AddParentProcess(parent_cache);
            child->GetProcessRole().AddRole(ProcessRole::PoolWorker);

            PROCESS_INFO("Execute child main function.");
            _run_main(std::forward<Args>(args)...);
            exit(0);
        } else {
            std::string child_name = name_;
            if (child_name.empty()) {
                child_name = parent->GetName() + "_" + std::to_string(pid);
            }
            ProcessID child_pid(pid);
            ProcessChild child(child_name, std::move(child_pid));
            if (auto_create_sockpair_) {
                pair[0].Close();
                child.SetFD(pair[1]);
            }
            child.SetDeadCallback(dead_callback_);
            child.GetRole().AddRole(ProcessRole::Child);
            child.SetState(ProcessState::Prepare);

            PROCESS_INFO("Register child [%d] into current process.", pid);
            parent->AddChildProcess(child);
            return {ProcessRet::SUCCESS, child_pid};
        }
        return {ProcessRet::SUCCESS, ProcessID(0)};
    }
private:
    mempool::MemPool* mempool_;         ///< Mempool pointer.
    std::string name_;                  ///< Process Name.
    F child_;                           ///< Process main function.
    bool auto_create_sockpair_;         ///< Auto create socketpair between process.
    void (*dead_callback_)(int*);       ///< Process dead callback for parent SIGCHLD.

    template <typename ... Args>
    ProcessRet _run_main(Args&& ... args) {
        child_(std::forward<Args>(args)...);
        return ProcessRet::SUCCESS;
    }
};

};

#endif
