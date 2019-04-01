#include <string.h>

#include "thread_log.h"
#include "thread_info.h"
#include "process_info.h"

#define MAX_THREAD_NAME_LEN (1024)

namespace thread {

thread_local ThreadInfo* ThreadInfo::pInstance = NULL;

ThreadInfo::ThreadInfo()
{
    tid_ = pthread_self();
    char name[MAX_THREAD_NAME_LEN];
    memset(name, 0x00, sizeof(name));
    sprintf(name, "_%lu", tid_);
    thread_name_.assign(name);
}

ThreadInfo::~ThreadInfo()
{

}

ThreadInfo* ThreadInfo::getInstance()
{
    if (!pInstance) {
        pInstance = new ThreadInfo();
    }
    return pInstance;
}

pthread_t ThreadInfo::GetTid()
{
    return tid_;
}

void ThreadInfo::SetThreadName(const char* name)
{
    if (!name)
        return;
    char cname[MAX_THREAD_NAME_LEN];
    memset(cname, 0x00, sizeof(cname));
    sprintf(cname, "%s_%lu", name, tid_);
    thread_name_.assign(cname);
}

std::string& ThreadInfo::GetThreadName()
{
    return thread_name_;
}

}
