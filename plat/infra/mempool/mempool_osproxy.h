#ifndef __MEMPOOL_OSPROXY_H__
#define __MEMPOOL_OSPROXY_H__

#include <stdlib.h>

namespace mempool {

class MemPoolOsProxy {
public:
    MemPoolOsProxy();
    ~MemPoolOsProxy();

    static void* alloc(size_t size);
    static void free(void* ptr);
};

};

#endif
