#ifndef __PROCESS_MUTEX_RW_LOCK_H__
#define __PROCESS_MUTEX_RW_LOCK_H__

#include "mutex_return.h"

namespace process::mutex {

class RWLock{
public:
    RWLock(){}
    virtual ~RWLock();
    virtual MutexRet RLock();
    virtual MutexRet RUnLock();
    virtual MutexRet WLock();
    virtual MutexRet WUnLock();
};

}

#endif
