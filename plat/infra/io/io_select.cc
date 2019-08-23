#include "io_defines.h"
#include "io_select.h"

namespace io {

Select::Select()
{
    efd_ = -1;
    init_flag_ = false;
}

Select::~Select()
{

}

IoRet Select::Initalize()
{
    if (init_flag_) {
        return IoRet::SUCCESS;
    }
    efd_ = epoll_create(SELECT_MAX_FD_SIZE);
    if (efd_ == -1) {
        init_flag_ = false;
        return errno;
    }
    return IoRet::SUCCESS;
}

IoRet Select::Listen()
{
    if (efd <= 0) {
        return IoRet::EINIT;
    }
    _traversal_select_item();
    for (;;) {
        int fd_num = epoll_wait(efd_, )
    }
}

IoRet Select::AddSelectItem(SelectItem& item)
{
    if (!item.GetFdPointer()) {
        return IoRet::IO_EBADSELECTITEM;
    }
    item.SetState(SelectItemState::Add);
    mutex_.lock();
    select_item_map_.insert_or_assign(item.GetFd(), item);
    mutex_.unlock();
    return IoRet::SUCCESS;
}

IoRet Select::DelSelectItem(FD& fd)
{

}

SelectItem Select::GetSelectItem(FD& fd)
{

}

void Select::_traversal_select_item()
{
    for (auto it : select_item_map_) {

    }
}

}
