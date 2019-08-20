#ifndef __IO_SELECT_ITEM_H__
#define __IO_SELECT_ITEM_H__

#include "io_fd.h"

namespace io {

class SelectItem {
public:
    SelectItem(FD& fd) {
        fd_ = fd;
    }
    ~SelectItem() { }


private:
    FD  fd_;
};

}

#endif
