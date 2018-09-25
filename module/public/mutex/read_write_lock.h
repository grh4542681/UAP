#ifndef __READ_WRITE_LOCK__
#define __READ_WRITE_LOCK__

#include "mutex_return.h"

namespace base {

class RWLock{
public:
    virtual MutexRet lock();
    virtual MutexRet unlock();
};

} // namespace base


#endif
