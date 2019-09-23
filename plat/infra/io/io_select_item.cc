#include "mempool.h"
#include "io_log.h"
#include "io_select_item.h"

namespace io {

SelectItem::SelectItem()
{

}

SelectItem::SelectItem(FD& fd)
{
    fd_ = fd.Clone();
}

SelectItem::SelectItem(const SelectItem& other)
{
    fd_ = other.fd_ ? other.fd_->Clone() : NULL;
    select_event_ = other.select_event_;
    state_ = other.state_;
    func_map_ = other.func_map_;
}

const SelectItem& SelectItem::operator=(const SelectItem& other)
{
    fd_ = other.fd_ ? other.fd_->Clone() : NULL;
    select_event_ = other.select_event_;
    state_ = other.state_;
    func_map_ = other.func_map_;
    return *this;
}

SelectItem::~SelectItem()
{
    if (fd_) {
        mempool::MemPool::getInstance()->Free<FD>(fd_);
    }
}

FD SelectItem::GetFd()
{
    return (fd_ ? *fd_ : FD());
}

FD* SelectItem::GetFdPointer()
{
    return fd_;
}

SelectItem::State SelectItem::GetState()
{
    return state_;
}

void SelectItem::SetState(SelectItem::State state)
{
    state_ = state;
}

IoRet SelectItem::AddEvent(int event, Callback func)
{
    if (!fd_) {
        return IoRet::EINIT;
    }
    auto it = func_map_.find(event);
    if (it == func_map_.end()) {
        return IoRet::IO_EUNKNOWEVENT;
    } else {
        it->second = func;
        return IoRet::SUCCESS;
    }
}

IoRet SelectItem::DelEvent(int event)
{
    return IoRet::SUCCESS;
}

bool SelectItem::HasEvent(int event)
{
    return (select_event_ | event);
}

SelectItem::Callback SelectItem::GetFunc(int event)
{
    auto it = func_map_.find(event);
    if (it == func_map_.end()) {
        return NULL;
    } else {
        return it->second;
    }
}

}
