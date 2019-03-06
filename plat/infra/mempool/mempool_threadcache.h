#ifndef __MEMPOOL_THREAD_CACHE_H__
#define __MEMPOOL_THREAD_CACHE_H__

#include <sys/types.h>
#include "mempool_center.h"

namespace mempool {

class MemPoolThreadCache {
public:
    MemPoolThreadCache();
    ~MemPoolThreadCache();
private:
    MemPoolCenter* center_;
    pid_t tid;
};

} //namespace ned

#endif
