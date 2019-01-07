#ifndef __THREAD_MUTEX_LOCK_H__
#define __THREAD_MUTEX_LOCK_H__

#include <pthread.h>
#include "thread_return.h"

namespace thread {

class ThreadMutexLock {
public:
    ThreadMutexLock();
    ~ThreadMutexLock();

    ThreadRet lock();
    ThreadRet unlock();
private:
    pthread_mutex_t mutex_;
    bool init_;

    //Don't allow copy
    ThreadMutexLock(const ThreadMutexLock&);
    ThreadMutexLock& operator = (const ThreadMutexLock&);
};

} //namepace mutex thread


#endif
