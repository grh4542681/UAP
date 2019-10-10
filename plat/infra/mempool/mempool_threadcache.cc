#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "file.h"

#include "mempool_threadcache.h"
#include "mempool_osproxy.h"

namespace mempool {

MemPoolThreadCache::MemPoolThreadCache()
{
    init_flag_ = false;
    tid_ = (pid_t)syscall(__NR_gettid);
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
            MEMPOOL_ERROR("Alloc from free list error");
            return NULL;
        }
        if ((ret = busy_list_.Insert(ptr, MemPoolItemOri::POOL)) != MemPoolRet::SUCCESS) {
            MEMPOOL_ERROR("Insert into bust list error");
            free_list_.Free(ptr);
            ptr = NULL;
            return NULL;
        }
    } else {
        ptr = MemPoolOsProxy::Alloc(size);
        if (!ptr) {
            MEMPOOL_ERROR("Alloc from os error");
            return NULL;
        }
        if ((ret = busy_list_.Insert(ptr, MemPoolItemOri::OS)) != MemPoolRet::SUCCESS) {
            MEMPOOL_ERROR("Insert into bust list error");
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
            MEMPOOL_ERROR("Unknow memory origon");
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
    sprintf(line, "Thread: %d\n", tid_);
    fd.GetFileFD().Write(line, sizeof(line));
    busy_list_.Report(fd);
}

} //namespace end
