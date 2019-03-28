#include "mempool_freelist.h"

namespace mempool {

MemPoolFreeList::MemPoolFreeList()
{
}

MemPoolFreeList::~MemPoolFreeList()
{

}

void* MemPoolFreeList::Alloc(size_t size)
{

}

void MemPoolFreeList::Free(void* ptr)
{

}

MemPoolRet MemPoolFreeList::Clear()
{
    return MemPoolRet::SUCCESS;
}

} //namespace end
