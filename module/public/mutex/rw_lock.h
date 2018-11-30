#ifndef __RW_LOCK_H__
#define __RW_LOCK_H__

#include "mutex_return.h"

namespace base {

class RWLock{
public:
    RWLock(){}
    virtual ~RWLock();
    virtual MutexRet RLock();
    virtual MutexRet RUnLock();
    virtual MutexRet WLock();
    virtual MutexRet WUnLock();
};

} // namespace base


#endif
