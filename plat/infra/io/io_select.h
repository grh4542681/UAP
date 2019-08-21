#ifndef __IO_SELECT_H__
#define __IO_SELECT_H__

#include <sys/epoll.h>

#include "io_select_item.h"

namespace io {

class Select {
public:
    Select();
    ~Select();

    void Listen();
    IoRet DelSelectItem(FD& fd);
    SelectItem& GetSelectItem(FD& fd);
private:
    bool init_flag_;
    int efd_;
    std::map<FD, SelectItem> select_map_;
};

}

#endif
