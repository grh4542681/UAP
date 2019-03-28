#include "mempool_busylist.h"

namespace mempool {

MemPoolBusyList::MemPoolBusyList()
{
    busy_map_.clear();
}

MemPoolBusyList::~MemPoolBusyList()
{
    busy_map_.clear();
}

MemPoolRet MemPoolBusyList::Insert(void* ptr, MemPoolItemOri ori)
{
    struct MemPoolBusyItem item;
    item.ptr_ = ptr;
    item.alloc_time_ = time(NULL);
    item.ori_ = ori;

    auto it = busy_map_.find(ptr);
    if (it != busy_map_.end()) {
        return MemPoolRet::EBUSYLISTDUPADDRESS;
    }

    std::pair<std::map<void*, MemPoolBusyItem>::iterator, bool> ret;
    ret = busy_map_.insert(std::pair<void*, MemPoolBusyItem>(ptr, item));
    if (ret.second==false) {
        return MemPoolRet::EBUSYLISTINSERT;
    }

    return MemPoolRet::SUCCESS;
}

MemPoolRet MemPoolBusyList::Remove(void* ptr)
{
    auto it = busy_map_.find(ptr);
    if (it == busy_map_.end()) {
        return MemPoolRet::EBUSYLISTNOTFOUND;
    }

    busy_map_.erase(it);
    return MemPoolRet::SUCCESS;
}

MemPoolItemOri MemPoolBusyList::Origin(void* ptr)
{
    auto it = busy_map_.find(ptr);
    if (it == busy_map_.end()) {
        return MemPoolItemOri::NONE;
    }
    return it->second.ori_;
}

unsigned int MemPoolBusyList::Size()
{
    return busy_map_.size();
}

MemPoolRet MemPoolBusyList::Clear()
{
    return MemPoolRet::SUCCESS;
}

};
