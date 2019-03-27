#include <stdlib.h>

#include "mempool_osproxy.h"

namespace mempool {

MemPoolOsProxy::MemPoolOsProxy()
{

}

MemPoolOsProxy::~MemPoolOsProxy()
{

}

void* MemPoolOsProxy::Alloc(size_t size)
{
    return malloc(size);
}

void MemPoolOsProxy::Free(void* ptr)
{
    return free(ptr);
}

}
