#include "io_defines.h"
#include "io_select.h"

namespace io {

Select::Select()
{
    efd_ = -1;
    init_flag_ = false;
    max_item_size_ = SELECT_MAX_FD_SIZE;
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

IoRet Select::Listen(timer::Time* overtime)
{
    return Listen(NULL, overtime);
}

IoRet Select::Listen(process::signal::ProcessSignalSet* sigmask, timer::Time* overtime)
{
    if (efd_ <= 0) {
        return IoRet::EINIT;
    }

    struct epoll_event rep_evts[max_item_size_];
    memset(rep_evts, 0, sizeof(epoll_event) * max_item_size_);

    sigset_t* set = sigmask ? sigmask->GetSigset() : NULL;
    int otime = overtime ? static_cast<int>(overtime->ToMilliseconds()) : -1;

    _traversal_select_item();
    for (;;) {
        int fd_num = epoll_pwait(efd_, rep_evts, max_item_size_, otime, set);
        if (fd_num == -1) {
            return errno;
        }
        for (int loop = 0; loop < fd_num; ++loop) {
            
        }
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
