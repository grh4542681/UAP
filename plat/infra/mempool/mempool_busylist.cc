#include <string.h>

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

void MemPoolBusyList::Report(file::File& fd)
{
    char line[1024];
    for (auto it : busy_map_) {
        memset(line, 0x00, sizeof(line));
        sprintf(line, "Address: %p\t alloctime: %lu\t", it.second.ptr_, it.second.alloc_time_);
        switch (it.second.ori_) {
            case MemPoolItemOri::OS:
                strcat(line, " ORI: OS");
                break;
            case MemPoolItemOri::POOL:
                strcat(line, " ORI: POOL");
                break;
            default:
                strcat(line, " ORI: Unknow");
                break;
        }
        strcat(line, "\n");
        fd.Write(line, sizeof(line));
    }
}

};
