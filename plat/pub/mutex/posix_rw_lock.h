#ifndef __POSIX_RW_LOCK_H__
#define __POSIX_RW_LOCK_H__

#include "mutex_return.h"
#include "rw_lock.h"

namespace base {

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

} // namespace base

#endif
