#ifndef _THREAD_SINGLE_INFO_H__
#define _THREAD_SINGLE_INFO_H__

#include <pthread.h>

namespace thread::single {

typedef struct _ThreadSingleInfo {
    pthread_t _tid;
    std::string _name;
}ThreadSingleInfo;

};

#endif