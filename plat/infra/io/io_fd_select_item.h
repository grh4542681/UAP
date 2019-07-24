#ifndef __IO_FD_SELECT_ITEM_H__
#define __IO_FD_SELECT_ITEM_H__

namespace io {

class FDSelectItem {
public:
    FDSelectItem(FD& fd) {
        fd_ = fd;
    }
    ~FDSelectItem() { }


protected:
    FD  fd_;
};

}

#endif
