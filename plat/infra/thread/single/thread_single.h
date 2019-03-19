#ifndef _THREAD_SINGLE_H__
#define _THREAD_SINGLE_H__

#include "thread_single_info.h"

namespace thread::single {

class ThreadSingle {
public:
    ThreadSingle();
    ~ThreadSingle();

    ThreadSingleInfo& getThreadInfo();

    template < typename F, typename ... Args>
    ThreadRet Run(F const& func, Args&& ... args) {
        _run(func, std::forward<Args>(args)...);
    }

private:
    thread_local ThreadSingleInfo _info;

private:
    void* _thread_single_main(void);
    template < typename F, typename ... Args>
    ThreadRet _run(F const& func, Args&& ... args);
};

};

#endif