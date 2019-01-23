#include <stdio.h>
#include "mempool.h"

namespace pub {

thread_local MemPool* MemPool::pInstance = NULL;

MemPool::MemPool()
{

}

MemPool::~MemPool()
{

}

void* MemPool::Malloc(size_t size)
{
    return malloc(size);
}

void MemPool::Free(void* ptr)
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
