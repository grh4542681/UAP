#ifndef __IO_EPOLL_FD__
#define __IO_EPOLL_FD__

#include "io_fd.h"
#include "io_select_event.h"

namespace io {

class EpollFD : public FD{
public:
    EpollFD();
    EpollFD(int flags);
    EpollFD(unsigned int fd, bool auto_close = false);
    EpollFD(EpollFD& other);
    ~EpollFD();

    //Inherited from class FD.
    ret::Return SetFD(unsigned int fd, bool auto_close);
    ret::Return Dup(io::FD& new_fd);
    io::FD* Clone();
    void Close();
    ssize_t Write(const void* data, size_t datalen);
    ssize_t Read(void* data, size_t datalen);

    IoRet AddEvent(FD& fd, int events);
    IoRet AddEvent(SelectEvent& event);
    IoRet ModEvent(FD& fd, int events);
    IoRet ModEvent(SelectEvent& event);
    IoRet DelEvent(FD& fd);
};

}

#endif
