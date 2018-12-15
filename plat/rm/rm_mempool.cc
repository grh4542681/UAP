#include "rm_mempool.h"

namespace rm{

thread_local RMMemPool* RMMemPool::pInstance = NULL;

RMMemPool::RMMemPool()
{

}

RMMemPool::~RMMemPool()
{

}

void* RMMemPool::Malloc(size_t size)
{
    return malloc(size);
}

void RMMemPool::Free(void* ptr)
{
    free(ptr);
}

RMMemPool* RMMemPool::getInstance()
{
    if (!pInstance) {
        pInstance = new RMMemPool();
    }
    return pInstance;
}

}// namespace rm end
