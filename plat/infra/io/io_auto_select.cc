#include "io_defines.h"
#include "io_auto_select.h"

namespace io {

AutoSelect::AutoSelect()
{
    efd_ = -1;
    init_flag_ = false;
    max_item_size_ = SELECT_MAX_FD_SIZE;
}

AutoSelect::~AutoSelect()
{

}

IoRet AutoSelect::Initalize()
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

IoRet AutoSelect::Listen(timer::Time* overtime)
{
    return Listen(NULL, overtime);
}

IoRet AutoSelect::Listen(process::signal::ProcessSignalSet* sigmask, timer::Time* overtime)
{
    if (efd_ <= 0) {
        return IoRet::EINIT;
    }

    struct epoll_event rep_evts[max_item_size_];
    memset(rep_evts, 0, sizeof(epoll_event) * max_item_size_);

    sigset_t* set = sigmask ? sigmask->GetSigset() : NULL;
    int otime = overtime ? static_cast<int>(overtime->ToMilliseconds()) : -1;

    for (;;) {

        if (_traversal_select_item() != IoRet::SUCCESS) {
            return IoRet::IO_EADDEVENT;
        }

        int fd_num = epoll_pwait(efd_, rep_evts, max_item_size_, otime, set);
        if (fd_num == -1) {
            return errno;
        }

        for (int loop = 0; loop < fd_num; ++loop) {
            auto it = select_item_map_.find(rep_evts[loop].data.fd);
            if (it == select_item_map_.end()) {
                return IoRet::IO_EUNKNOWFD;
            } else {
                if (rep_evts[loop].events | EPOLLIN) {
                    if (it->second->HasEvent(EPOLLIN)) {
                        SelectItem::Callback func = it->second->GetFunc(EPOLLIN);
                        if (!func) {
                            return IoRet::IO_ENOCALLBACK;
                        } else {
                            func(it->second);
                printf("--%d---grh\n", __LINE__);
                        }
                    } else {
                        return IoRet::IO_EMATCHEVENT;
                    }
                }
                if (rep_evts[loop].events | EPOLLOUT) {
                }
            }
        }
    }
}

IoRet AutoSelect::AddSelectItem(SelectItem* item)
{
    if (!item->GetFdPointer()) {
        return IoRet::IO_EBADSELECTITEM;
    }
    item->SetState(SelectItem::State::Add);
    mutex_.lock();
    select_item_map_.insert_or_assign(item->GetFd(), item);
    printf("--%d--%d-grh\n", __LINE__, item->GetFd().GetFD());
    mutex_.unlock();
    return IoRet::SUCCESS;
}

IoRet AutoSelect::DelSelectItem(FD& fd)
{

}

SelectItem AutoSelect::GetSelectItem(FD& fd)
{

}

IoRet AutoSelect::_traversal_select_item()
{
    for (auto it = select_item_map_.begin(); it != select_item_map_.end(); it++) {
        switch (it->second->state_) {
            case SelectItem::State::Normal:
                break;
            case SelectItem::State::Add:
                struct epoll_event event;
                memset(&event, 0, sizeof(struct epoll_event));
                event.events = it->second->select_event_;
                event.events |= EPOLLET;
                event.data.fd = it->second->fd_->GetFD();
                if (epoll_ctl(efd_, EPOLL_CTL_ADD, it->second->fd_->GetFD(), &event) == -1) {
                }
                it->second->state_ = SelectItem::State::Normal;
                break;
            case SelectItem::State::Delete:
                if (epoll_ctl(efd_, EPOLL_CTL_DEL, it->second->fd_->GetFD(), NULL) == -1) {
                }
                select_item_map_.erase(it);
                break;
            case SelectItem::State::Update:
                break;
            default:
                break;
        }
    }
    return IoRet::SUCCESS;
}

}
