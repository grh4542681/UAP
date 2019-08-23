#ifndef __IO_SELECT_ITEM_H__
#define __IO_SELECT_ITEM_H__

#include <sys/epoll.h>

#include "io_defines.h"
#include "io_fd.h"

namespace io {

enum class SelectItemState {
    Normal,
    Add,
    Delete,
    Update,
};

class SelectItem {
public:
    typedef IoRet (*Callback)(SelectItem* item);
public:
    SelectItem();
    SelectItem(FD& fd);
    SelectItem(const SelectItem& other);
    ~SelectItem();

    const SelectItem& operator=(const SelectItem& other);

    FD GetFd();
    FD* GetFdPointer();

    SelectItemState GetState();
    void SetState(SelectItemState state);

    IoRet AddEvent(int event, Callback func);
    IoRet DelEvent(int event);
    Callback GetFunc(int event);
private:
    FD*  fd_ = NULL;
    int select_event_ = 0;
    SelectItemState state_ = SelectItemState::Normal;
    std::map<int, Callback> func_map_ = {
        { SELECT_INPUT, NULL },
        { SELECT_OUTPUT, NULL },
        { SELECT_HANGUP, NULL },
        { SELECT_ERROR, NULL },
    };
};

}

#endif
