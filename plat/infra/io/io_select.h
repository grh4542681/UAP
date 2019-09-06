#ifndef __IO_SELECT_H__
#define __IO_SELECT_H__

#include <sys/epoll.h>

#include "mutex/thread_mutex_lock.h"
#include "signal/process_signal_set.h"
#include "vtime.h"
#include "io_select_item.h"

namespace io {

class Select {
public:
    Select();
    ~Select();

    IoRet Initalize();
    IoRet AddSelectItem(SelectItem* item);
    IoRet DelSelectItem(FD& fd);
    SelectItem GetSelectItem(FD& fd);

    IoRet Listen(timer::Time* overtime);
    IoRet Listen(process::signal::ProcessSignalSet* sigmask, timer::Time* overtime);
private:
    bool init_flag_;
    int efd_;
    size_t max_item_size_;
    std::map<FD, SelectItem*, std::less<>> select_item_map_;
    thread::mutex::ThreadMutexLock mutex_;

    IoRet _traversal_select_item();
};

}

#endif
