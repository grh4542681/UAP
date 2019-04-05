#ifndef _THREAD_SINGLE_H__
#define _THREAD_SINGLE_H__

#include <thread>
#include <future>
#include <utility>
#include <functional>
#include <type_traits>

#include "thread_info.h"

namespace thread::single {

class ThreadSingleRet {

};

template < typename F, typename R = ThreadSingleRet >
class ThreadSingle {
public:
    ThreadSingle(F func) {
        running_flag_= false;
        func_ = func;
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
        thread_ = std::thread(&ThreadSingle::_run_main<Args ...>, this, std::forward<Args>(args)...);
        running_flag_ = true;
        return ThreadRet::SUCCESS;
    }

    ThreadRet Join() {
        thread_.join();
        return ThreadRet::SUCCESS;
    }

    R& Return() {
        return ret_;
    }

private:
    ThreadInfo* thread_info_;
private:
    F func_;
    bool running_flag_;
    std::thread thread_;
    R ret_;

    template <typename ... Args>
    ThreadRet _run_main(Args&& ... args) {
        thread_info_ = ThreadInfo::getInstance();
        thread_info_->Register2Process();

        ret_ = func_(std::forward<Args>(args)...);

        thread_info_->Unregister2Process();
        ThreadInfo::freeInstance();
        return ThreadRet::SUCCESS;
    }

};

template < typename F >
class ThreadSingle <F, ThreadSingleRet> {
public:
    ThreadSingle(F func) {
        running_flag_= false;
        func_ = func;
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
        thread_ = std::thread(&ThreadSingle::_run_main<Args ...>, this, std::forward<Args>(args)...);
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
    ThreadRet _run_main(Args&& ... args) {
        thread_info_ = ThreadInfo::getInstance();
        thread_info_->Register2Process();

        func_(std::forward<Args>(args)...);

        thread_info_->Unregister2Process();
        ThreadInfo::freeInstance();
        return ThreadRet::SUCCESS;
    }

};

};

#endif
