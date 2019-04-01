#ifndef __THREAD_H__
#define __THREAD_H__

#include "thread_log.h"
#include "thread_return.h"
#include "thread_info.h"
#include "process_info.h"

namespace thread {

ThreadRet RegisterThread()
{
    ThreadInfo* thread_info = ThreadInfo::getInstance();
    process::ProcessInfo* process_info = process::ProcessInfo::getInstance();
    if (process_info->AddThreadInfo(thread_info) != process::ProcessRet::SUCCESS ) {
        return ThreadRet::THREAD_EREGISTER;
    }
    return ThreadRet::SUCCESS;
}

ThreadRet RegisterThread(const char* name)
{
    ThreadInfo* thread_info = ThreadInfo::getInstance();
    thread_info->SetThreadName(name);
    process::ProcessInfo* process_info = process::ProcessInfo::getInstance();
    if (process_info->AddThreadInfo(thread_info) != process::ProcessRet::SUCCESS ) {
        return ThreadRet::THREAD_EREGISTER;
    }
    return ThreadRet::SUCCESS;
}

ThreadRet UnregisterThread() 
{
    ThreadInfo* thread_info = ThreadInfo::getInstance();
    process::ProcessInfo* process_info = process::ProcessInfo::getInstance();
    if (process_info->DelThreadInfo(thread_info->GetTid()) != process::ProcessRet::SUCCESS ) {
        return ThreadRet::THREAD_EUNREGISTER;
    }
    return ThreadRet::SUCCESS;
}

void SetThreadName(const char* name)
{
    ThreadInfo* thread_info = ThreadInfo::getInstance();
    thread_info->SetThreadName(name);
}

std::string& GetThreadName()
{
    ThreadInfo* thread_info = ThreadInfo::getInstance();
    return thread_info->GetThreadName();
}

}

#endif
