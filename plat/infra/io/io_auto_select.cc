#include "io_log.h"
#include "io_defines.h"
#include "io_auto_select.h"

namespace io {

AutoSelect::AutoSelect()
{
    efd_ = -1;
    item_size_ = SELECT_MAX_FD_SIZE;
    efd_ = epoll_create(SELECT_MAX_FD_SIZE);
    if (efd_ == -1) {
        init_flag_ = false;
        IO_ERROR("Create epoll error : %s", strerror(errno));
    }
    init_flag_ = true;
}

AutoSelect::~AutoSelect()
{

}

auto& AutoSelect::GetListenrThread()
{
    return listener_thread_;
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

    struct epoll_event rep_evts[item_size_];
    memset(rep_evts, 0, sizeof(epoll_event) * item_size_);

    sigset_t* set = sigmask ? sigmask->GetSigset() : NULL;
    int otime = overtime ? static_cast<int>(overtime->ToMilliseconds()) : -1;

    for (;;) {

        if (_select_item_traversal() != IoRet::SUCCESS) {
            return IoRet::IO_EADDEVENT;
        }

        int fd_num = epoll_pwait(efd_, rep_evts, item_size_, otime, set);
        if (fd_num == -1) {
            return errno;
        }

        for (int loop = 0; loop < fd_num; ++loop) {
            auto it = select_item_map_.find(rep_evts[loop].data.fd);
            if (it == select_item_map_.end()) {
                return IoRet::IO_EUNKNOWFD;
            } else {
                it->second->Callback();
            }
        }
    }
}

template <typename T, typename ... Args>
IoRet AddSelectItem(Args&& ... args)
{

}

IoRet AutoSelect::DelSelectItem(FD& fd)
{

}

IoRet AutoSelect::ModSelectItem()
{

}

const SelectItem& AutoSelect::GetSelectItem(FD& fd)
{

}

IoRet AutoSelect::_select_item_traversal()
{
    return IoRet::SUCCESS;
}

IoRet AutoSelect::_select_listener_thread_handler()
{

}

}
