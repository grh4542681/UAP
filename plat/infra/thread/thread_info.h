#ifndef _THREAD_INFO_H__
#define _THREAD_INFO_H__

#include <pthread.h>
#include <string>

#include "thread_return.h"

namespace thread {

class ThreadInfo {
public:
    static ThreadInfo* getInstance();

    pthread_t GetTid();
    std::string& GetThreadName();
    void SetThreadName(const char* name);

private:
    ThreadInfo();
    ~ThreadInfo();

    pthread_t tid_;
    std::string thread_name_;

    thread_local static ThreadInfo* pInstance;
};


};

#endif
