#ifndef __IO_SELECT_ITEM_H__
#define __IO_SELECT_ITEM_H__

#include <sys/epoll.h>

#include "io_defines.h"
#include "io_fd.h"
#include "io_select_event.h"

namespace io {


class SelectItem {
public:
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

    SelectItem::State GetState();
    SelectItem& SetState(State state);

    virtual IoRet Callback(){
        return IoRet::ESUBCLASS;
    }

private:
    SelectEvent event_;
    State state_ = State::Normal;
};

}

#endif
