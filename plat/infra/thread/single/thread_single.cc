#include "thread_single.h"
#include "thread_info.h"

namespace thread::single {

template < typename F >
ThreadSingle<F>::ThreadSingle()
{
    running_flag_= false;
}

template < typename F >
ThreadSingle<F>::~ThreadSingle()
{

}

template < typename F >
ThreadInfo* ThreadSingle<F>::GetThreadInfo()
{
    return thread_info_;
}

template < typename F >
template < typename ... Args >
ThreadRet ThreadSingle<F>::Run(Args&& ... args)
{
    if (running_flag_) {
        return ThreadRet::THREAD_ERUNNING;
    }
    thread_ = std::thread(_run, std::forward<Args>(args)...);
    running_flag_ = true;
    return ThreadRet::SUCCESS;
}

template < typename F >
template < typename ... Args >
ThreadRet ThreadSingle<F>::_run(Args&& ... args)
{
    thread_info_ = ThreadInfo::getInstance();
    thread_info_->Register2Process();
    func_(std::forward<Args>(args)...);
    return ThreadRet::SUCCESS;
}

template < typename F >
ThreadRet ThreadSingle<F>::Join()
{
    thread_.join();
    return ThreadRet::SUCCESS;
}

}
