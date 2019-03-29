#include <string.h>

#include "mempool_threadcache.h"
#include "mempool_osproxy.h"

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
            return NULL;
        }
        if ((ret = busy_list_.Insert(ptr, MemPoolItemOri::POOL)) != MemPoolRet::SUCCESS) {
            free_list_.Free(ptr);
            ptr = NULL;
            return NULL;
        }
    } else {
        ptr = MemPoolOsProxy::Alloc(size);
        if (!ptr) {
            return NULL;
        }
        if ((ret = busy_list_.Insert(ptr, MemPoolItemOri::OS)) != MemPoolRet::SUCCESS) {
            MemPoolOsProxy::Free(ptr);
            ptr = NULL;
            return NULL;
        }
    }
    return ptr;
}

void MemPoolThreadCache::Free(void* ptr)
{
    if (!ptr) {
        return;
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
            MEMPOOL_ERROR("Free address %p is untrack address.", ptr);
            return;
        default:
            return;
    }
}

void MemPoolThreadCache::Report(int fd)
{
    //Report(file::File(fd));
}

void MemPoolThreadCache::Report(file::File& fd)
{
    char line[1024];
    memset(line, 0x00, sizeof(line));
    sprintf(line, "Thread: %lu\n", tid_);
    fd.Write(line, sizeof(line));
    busy_list_.Report(fd);
}

} //namespace end
