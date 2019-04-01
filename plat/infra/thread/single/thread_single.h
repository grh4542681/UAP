#ifndef _THREAD_SINGLE_H__
#define _THREAD_SINGLE_H__

#include "thread.h"

namespace thread::single {

class ThreadSingle {
public:
    ThreadSingle();
    ~ThreadSingle();

    ThreadInfo* GetThreadInfo();

    template < typename F, typename ... Args>
    ThreadRet Run(F const& func, Args&& ... args) {
        _run(func, std::forward<Args>(args)...);
    }

private:
    ThreadInfo* thread_info_;
private:
    void* _thread_single_main(void);
    template < typename F, typename ... Args>
    ThreadRet _run(F const& func, Args&& ... args);
};

};

#endif
