#ifndef __IO_SELECT_EVENT_H__
#define __IO_SELECT_EVENT_H__

#include <sys/epoll.h>

namespace io {

enum class SelectEvent : int {
    INPUT = EPOLLIN,
    OUTPUT = EPOLLOUT,
    HANGUP = EPOLLHUP,
    ERROR = EPOLLERR,
};

}

#endif
