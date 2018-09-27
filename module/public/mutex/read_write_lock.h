#ifndef __READ_WRITE_LOCK_H__
#define __READ_WRITE_LOCK_H__

#include "mutex_return.h"

namespace base {

class RWLock{
public:
    virtual MutexRet RLock();
    virtual MutexRet RUnLock();
    virtual MutexRet WLock();
    virtual MutexRet WUnLock();
};

} // namespace base


#endif
