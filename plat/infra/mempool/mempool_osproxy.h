#ifndef __MEMPOOL_OSPROXY_H__
#define __MEMPOOL_OSPROXY_H__

#include <stdlib.h>

namespace mempool {

class MemPoolOsProxy {
public:
    MemPoolOsProxy();
    ~MemPoolOsProxy();

    static void* Alloc(size_t size);
    static void Free(void* ptr);
};

};

#endif
