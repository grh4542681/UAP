#ifndef __IO_SELECT_H__
#define __IO_SELECT_H__

#include <sys/epoll.h>

#include "mutex/thread_mutex_lock.h"
#include "io_select_item.h"

namespace io {

class Select {
public:
    Select();
    ~Select();

    IoRet Initalize();
    IoRet Listen();
    IoRet AddSelectItem(SelectItem& item);
    IoRet DelSelectItem(FD& fd);
    SelectItem GetSelectItem(FD& fd);
private:
    bool init_flag_;
    int efd_;
    std::map<FD, SelectItem> select_item_map_;
    thread::mutex::ThreadMutexLock mutex_;

    void _traversal_select_item();
};

}

#endif
