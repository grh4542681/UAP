#ifndef __IO_SELECT_ITEM_H__
#define __IO_SELECT_ITEM_H__

#include <sys/epoll.h>

#include "io_defines.h"
#include "io_fd.h"

namespace io {


class Select;
class SelectItem {
public:
    friend class Select;
    friend class AutoSelect;
    typedef IoRet (*Callback)(SelectItem* item);
    enum Event {
        Input = EPOLLIN,
        Output = EPOLLOUT,
        Error = EPOLLERR,
    };
    enum class State {
        Normal,
        Add,
        Delete,
        Update,
    };
public:
    SelectItem();
    SelectItem(FD& fd);
    SelectItem(const SelectItem& other);
    virtual ~SelectItem();

    const SelectItem& operator=(const SelectItem& other);

    FD GetFd();
    FD* GetFdPointer();

    SelectItem::State GetState();
    void SetState(State state);

    IoRet AddEvent(int event, Callback func);
    IoRet DelEvent(int event);
    bool HasEvent(int event);
    Callback GetFunc(int event);
private:
    FD* fd_;
    int select_event_ = 0;
    State state_ = State::Add;
    std::map<int, Callback> func_map_ = {
        { SELECT_INPUT, NULL },
        { SELECT_OUTPUT, NULL },
        { SELECT_HANGUP, NULL },
        { SELECT_ERROR, NULL },
    };
};

}

#endif
