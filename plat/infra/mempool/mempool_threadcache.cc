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
    return MemPoolRet::ERROR;
}

void* MemPoolThreadCache::Alloc(size_t size)
{
    MemPoolRet ret = MemPoolRet::SUCCESS;
    void* ptr = NULL;

    if (init_flag_) {
        ptr = free_list_.Alloc(size);
        if (!ptr) {
            return MemPoolRet::EALLOC;
        }
        if ((ret = busy_list_.Insert(ptr, MemPoolItemOri::POOL)) != MemPoolRet::SUCCESS) {
            free_list_.Free(ptr);
            ptr = NULL;
            return ret;
        }
    } else {
        ptr = MemPoolOsProxy::Alloc(size);
        if (!ptr) {
            return MemPoolRet::EALLOC;
        }
        if ((ret = busy_list_.Insert(ptr, MemPoolItemOri::OS)) != MemPoolRet::SUCCESS) {
            MemPoolOsProxy::Free(ptr);
            ptr = NULL;
            return ret;
        }
    }
    return ptr;
}

void MemPoolThreadCache::Free(void* ptr)
{
    if (!ptr) {
        return MemPoolRet::EBADARGS;
    }
    MemPoolItemOri origin = busy_list_.Origin(ptr);
    switch (origin) {
        case MemPoolItemOri::OS:
            MemPoolOsProxy::Free(ptr);
            busy_list_.Remove(ptr);
            return;
        case MemPoolItemOri::POOL:
            free_list_.Free(ptr);
            busy_list_.Remove(ptr);
            return;
        case MemPoolItemOri::NONE:
            MEMPOOL_ERROR("Free address %p is untrack address.");
            return;
        default:
            return;
    }
}

} //namespace end
