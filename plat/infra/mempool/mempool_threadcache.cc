#include "mempool_threadcache.h"

namespace mempool {

MemPoolThreadCache::MemPoolThreadCache()
{
    init_flag_ = false;
    tid_ = pthread_self();
    center_ = NULL;
    if (busy_list_.Clear() != MemPoolRet::SUCCESS) {
        MEMPOOL_ERROR("busy list clear error");
    }   
    if (free_list_.Clear() != MemPoolRet::SUCCESS) {
        MEMPOOL_ERROR("free list clear error");
    }
    if (Init() == MemPoolRet::SUCCESS) {
        init_flag_ = true;
    }
}

MemPoolThreadCache::~MemPoolThreadCache()
{

}

MemPoolRet MemPoolThreadCache::Init()
{

}

void* MemPoolThreadCache::Alloc(size_t size)
{

}

void MemPoolThreadCache::Free(void* ptr)
{

}

} //namespace end
