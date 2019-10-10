#ifndef __MEMPOOL_THREAD_CACHE_H__
#define __MEMPOOL_THREAD_CACHE_H__

#include <sys/types.h>

#include "mempool_center.h"
#include "mempool_freelist.h"
#include "mempool_busylist.h"

namespace file {
class File;
}

namespace mempool {

class MemPoolThreadCache {
public:
    MemPoolThreadCache();
    ~MemPoolThreadCache();

    MemPoolRet Init();

    void* Alloc(size_t size);
    void Free(void* ptr);

    void Report(int fd);
    void Report(file::File& fd);
private:
    bool init_flag_;
    pid_t tid_;
    MemPoolCenter* center_;
    MemPoolFreeList free_list_;
    MemPoolBusyList busy_list_;
};

} //namespace ned

#endif
