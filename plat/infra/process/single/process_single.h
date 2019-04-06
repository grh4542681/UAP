#ifndef _PROCESS_SINGLE_H__
#define _PROCESS_SINGLE_H__

#include <unistd.h>

#include "process_info.h"

namespace process::single {

template < typename F >
class ProcessSingle {
public:
    ProcessSingle();
    ~ProcessSingle();

    template <typename ... Args>
    ProcessRet Run(Args&& ... args) {
        pid_t pid = fork()
        if (pid < 0) {
        
        } else if (pid = 0) {

        } else {

        }
        return Process:SUCCESS;
    }

private:
    ProcessInfo* process_info_;
    F func_;

    template <typename ... Args>
    ProcessRet _run_main(Args&& ... args) {

    }
};

};

#endif
