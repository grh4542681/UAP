#include <utility>
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

template < typename T, typename ... Args>
T* RMMemPool::Malloc(Args&& ... args)
{
    T* ptr = malloc(sizeof(T));
    memset(ptr, 0x00, sizeof(T));
    return (new(ptr) T(std::forward<Args>(args)...));
}

template < typename T >
void RMMemPool::Free(T* ptr)
{
    ptr->~T();
    free(ptr);
}

template < typename T, typename ... Args>
T* RMMemPool::Reset(T* ptr, Args&& ... args)
{
    ptr->~T();
    memset(ptr, 0x00, sizeof(T));
    return (new(ptr) T(std::forward<Args>(args)...));
}

RMMemPool* RMMemPool::getInstance()
{
    if (!pInstance) {
        pInstance = new RMMemPool();
    }
    return pInstance;
}

}// namespace rm end
