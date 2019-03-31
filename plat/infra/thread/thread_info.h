#ifndef _THREAD_INFO_H__
#define _THREAD_INFO_H__

#include <pthread.h>
#include <string>

namespace thread {

class ThreadInfo {
public:
    static ThreadInfo* getInstance();
    static ThreadInfo* getInstance(const char* cname);

    pthread_t GetTid();
    std::string& GetThreadName();
    void SetThreadName(const char* name);

private:
    ThreadInfo();
    ThreadInfo(const char* name);
    ~ThreadInfo();

    pthread_t tid_;
    std::string thread_name_;

    thread_local static ThreadInfo* pInstance;
};

};

#endif
