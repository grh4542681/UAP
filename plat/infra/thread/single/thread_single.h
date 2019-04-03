#ifndef _THREAD_SINGLE_H__
#define _THREAD_SINGLE_H__

#include <thread>

#include "thread_info.h"

namespace thread::single {

template < typename F >
class ThreadSingle {
public:
    ThreadSingle() {
        running_flag_= false;
    }

    ~ThreadSingle() {

    }

    ThreadInfo* GetThreadInfo() {
        return thread_info_;
    }

    template <typename ... Args>
    ThreadRet Run(Args&& ... args) {
        if (running_flag_) {
            return ThreadRet::THREAD_ERUNNING;
        }
        thread_ = std::thread(_run, std::forward<Args>(args)...);
        running_flag_ = true;
        return ThreadRet::SUCCESS;
    }

    ThreadRet Join() {
        thread_.join();
        return ThreadRet::SUCCESS;
    }

private:
    ThreadInfo* thread_info_;
private:
    F func_;
    bool running_flag_;
    std::thread thread_;

    template <typename ... Args>
    ThreadRet _run(Args&& ... args) {
        thread_info_ = ThreadInfo::getInstance();
        thread_info_->Register2Process();
        func_(std::forward<Args>(args)...);
        return ThreadRet::SUCCESS;
    }

};

};

#endif
