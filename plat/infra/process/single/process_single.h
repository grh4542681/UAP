#ifndef _PROCESS_SINGLE_H__
#define _PROCESS_SINGLE_H__

#include <unistd.h>
#include <type_traits>

#include "process_info.h"

namespace process::single {

template < typename F >
class ProcessSingle {
public:
    ProcessSingle(F child) {
        child_ = child;
    }
    ~ProcessSingle();

    template <typename ... Args>
    ProcessRet Run(Args&& ... args) {
        if (!std::is_function(F)) {
            return ProcessRet::PROCESS_ECALLABLE;
        }

        int fd[2];
        if (socketpair( AF_UNIX, SOCK_STREAM, 0, fd ) < 0 ) {
            return ProcessRet::ERROR;
        }

        pid_t pid = fork()
        if (pid < 0) {
            return ProcessRet::PROCESS_EFORK;
        } else if (pid = 0) {
            return _run_main(std::forward<Args>(args)...);
        } else {

        }
        return Process:SUCCESS;
    }

private:
    ProcessInfo* process_info_;
    F child_;

    template <typename ... Args>
    ProcessRet _run_main(Args&& ... args) {

        return child_(std::forward<Args>(args)...);
    }
};

};

#endif
