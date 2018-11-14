#ifndef __PTHREAD_MUTEX_LOCK_H__
#define __PTHREAD_MUTEX_LOCK_H__

#include <pthread.h>
#include "mutex_return.h"

namespace base {

class PthreadMutexLock {
public:
    PthreadMutexLock();
    ~PthreadMutexLock();

    MutexRet lock();
    MutexRet unlock();
private:
    pthread_mutex_t _mutex;
    bool _init;

    //Don't allow copy
    PthreadMutexLock(const PthreadMutexLock&);
    PthreadMutexLock& operator = (const PthreadMutexLock&);
};

} //namepace mutex end


#endif
