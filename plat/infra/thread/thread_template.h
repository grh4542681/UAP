#ifndef _THREAD_SINGLE_H__
#define _THREAD_SINGLE_H__

#include <thread>
#include <future>
#include <utility>
#include <functional>
#include <type_traits>

#include "thread_info.h"

namespace thread {

class ThreadTemplateRet {

};

template < typename F, typename R = ThreadTemplateRet >
class ThreadTemplate {
public:
    ThreadTemplate(F func) {
        running_flag_= false;
        func_ = func;
    }

    ~ThreadTemplate() {

    }

    ThreadInfo* GetThreadInfo() {
        return thread_info_;
    }

    template <typename ... Args>
    ThreadRet Run(Args&& ... args) {
        if (running_flag_) {
            return ThreadRet::THREAD_ERUNNING;
        }
        thread_ = std::thread(&ThreadTemplate::_run_main<Args ...>, this, std::forward<Args>(args)...);
        running_flag_ = true;
        return ThreadRet::SUCCESS;
    }

    ThreadRet Join() {
        thread_.join();
        return ThreadRet::SUCCESS;
    }

    void Detach() {
        thread_.detach();
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
//        thread_info_->thread_ = &thread_;
        thread_info_->Register2Process();

        ret_ = func_(std::forward<Args>(args)...);

        thread_info_->Unregister2Process();
        ThreadInfo::freeInstance();
        return ThreadRet::SUCCESS;
    }

};

template < typename F >
class ThreadTemplate <F, ThreadTemplateRet> {
public:
    ThreadTemplate(F func) {
        running_flag_= false;
        func_ = func;
    }

    ~ThreadTemplate() {

    }

    ThreadInfo* GetThreadInfo() {
        return thread_info_;
    }

    template <typename ... Args>
    ThreadRet Run(Args&& ... args) {
        if (running_flag_) {
            return ThreadRet::THREAD_ERUNNING;
        }
        thread_ = std::thread(&ThreadTemplate::_run_main<Args ...>, this, std::forward<Args>(args)...);
        running_flag_ = true;
        return ThreadRet::SUCCESS;
    }

    ThreadRet Join() {
        thread_.join();
        return ThreadRet::SUCCESS;
    }

    void Detach() {
        thread_.detach();
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
//        thread_info_->thread_ = &thread_;
        thread_info_->Register2Process();

        func_(std::forward<Args>(args)...);

        thread_info_->Unregister2Process();
        ThreadInfo::freeInstance();
        return ThreadRet::SUCCESS;
    }

};

};

#endif
