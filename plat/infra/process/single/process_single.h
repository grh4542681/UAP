#ifndef _PROCESS_SINGLE_H__
#define _PROCESS_SINGLE_H__

#include <unistd.h>
#include <type_traits>

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
    ~ProcessSingle();

    template <typename ... Args>
    ProcessRet Run(Args&& ... args) {
        if (!std::is_function(F)) {
            return ProcessRet::PROCESS_ECALLABLE;
        }
        if (fifo_.Open() != IpcRet::SUCCESS) {
            return ProcessRet::PROCESS::EFIFOPAIR;
        }
        pid_t pid = fork()
        if (pid < 0) {
            fifo_.Close();
            return ProcessRet::PROCESS_EFORK;
        } else if (pid = 0) {
            ProcessInfo* process_info = ProcessInfo::getInstance();
            process_info.fifo_ = fifo_;
            return _run_main(std::forward<Args>(args)...);
        } else {
            run_flag_ = true;
        }
        return Process:SUCCESS;
    }

private:
    mempool::MemPool* mempool_;
    bool run_flag_;
    ProcessInfo* process_info_;
    F child_;

    template <typename ... Args>
    ProcessRet _run_main(Args&& ... args) {

        return child_(std::forward<Args>(args)...);
    }
};

};

#endif
