#include <stdlib.h>

#include "mempool_osproxy.h"

namespace mempool {

MemPoolOsProxy::MemPoolOsProxy()
{

}

MemPoolOsProxy::~MemPoolOsProxy{

}

static void* MemPoolOsProxy::alloc(size_t size)
{
    return malloc(size);
}

static void MemPoolOsProxy::free(void* ptr)
{
    return free(ptr);
}

}
