#ifndef __IO_AUTO_SELECT_H__
#define __IO_AUTO_SELECT_H__

#include <sys/epoll.h>

#include "thread_template.h"
#include "mutex/thread_mutex_lock.h"
#include "signal/process_signal_set.h"
#include "timer_time.h"
#include "timer_fd.h"

#include "io_epoll_fd.h"
#include "io_select_item.h"

namespace io {

class AutoSelect {
public:
    AutoSelect();
    ~AutoSelect();

    template <typename T, typename ... Args> IoRet AddSelectItem(Args&& ... args);
    IoRet DelSelectItem(FD& fd);
    IoRet ModSelectItem();
    const SelectItem& GetSelectItem(FD& fd);

    auto& GetListenrThread();

    IoRet Listen(timer::Time* overtime);
    IoRet Listen(process::signal::ProcessSignalSet* sigmask, timer::Time* overtime);

    //static IoRet _select_listener_thread_handler(AutoSelect* instance, process::signal::ProcessSignalSet* sigmask, timer::Time* overtime);
    static IoRet _select_listener_thread_handler(timer::Time* overtime);
private:
    bool init_flag_;
    EpollFD fd_;

    thread::mutex::ThreadMutexLock mutex_;
    std::map<int, SelectItem*> select_item_map_;

    thread::ThreadTemplate<decltype(&_select_listener_thread_handler), IoRet> listener_thread_;

    IoRet _select_item_traversal();
};

}

#endif
