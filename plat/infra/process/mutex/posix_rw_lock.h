#ifndef __PROCESS_MUTEX_POSIX_RW_LOCK_H__
#define __PROCESS_MUTEX_POSIX_RW_LOCK_H__

#include "mutex_return.h"
#include "rw_lock.h"

namespace infra::process::mutex {

class PosixRWLock : public RWLock{
public:
    PosixRWLock();
    ~PosixRWLock();

    MutexRet RLock();
    MutexRet RUnLock();
    MutexRet WLock();
    MutexRet WUnLock();
private:
    
};

}

#endif
