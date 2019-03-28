#include <stdio.h>
#include "mempool.h"
#include "mempool_center.h"

namespace mempool {

thread_local MemPool* MemPool::pInstance = NULL;

MemPool::MemPool()
{
}

MemPool::~MemPool()
{

}

void* MemPool::_malloc(size_t size)
{
    printf("---%d---%s--\n",__LINE__,__FILE__);
    return threadcache_.Alloc(size);
}

void MemPool::_free(void* ptr)
{
    threadcache_.Free(ptr);
}

MemPool* MemPool::getInstance()
{
    if (!pInstance) {
    printf("---%d---%s--\n",__LINE__,__FILE__);
        pInstance = new MemPool();
    printf("---%d---%s--\n",__LINE__,__FILE__);
    }
    return pInstance;
}

}// namespace pub end
