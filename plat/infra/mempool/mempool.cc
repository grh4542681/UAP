#include <stdio.h>
#include "mempool.h"
#include "mempool_center.h"

namespace mempool {

thread_local MemPool* MemPool::pInstance = NULL;

MemPool::MemPool()
{
    pcenter_ = MemPoolCenter::getInstance();
}

MemPool::~MemPool()
{

}

void* MemPool::_malloc(size_t size)
{
    return malloc(size);
}

void MemPool::_free(void* ptr)
{
    free(ptr);
}

MemPool* MemPool::getInstance()
{
    if (!pInstance) {
        pInstance = new MemPool();
    }
    return pInstance;
}

}// namespace pub end
