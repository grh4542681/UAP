#ifndef __EVENT_FD_H__
#define __EVENT_FD_H__

#include <sys/eventfd.h>

#include "io_fd.h"

#include "ipc_return.h"

namespace ipc::event {

class EventFD : public io::FD {
public:
    enum Flag {
        CloseExec,
        Nonblock,
        Semaphore,
    };
public:
    EventFD();
    EventFD(int initval, int flag);
    EventFD(unsigned int fd, bool auto_close = false);
    EventFD(EventFD& other);
    ~EventFD();

    //Inherited from class FD.
    ret::Return SetFD(unsigned int fd, bool auto_close);
    ret::Return Dup(io::FD& new_fd);
    io::FD* Clone();
    void Close();
    size_t Write(const void* data, size_t datalen);
    size_t Read(void* data, size_t datalen);

private:
    int flag_ = 0;
};

}

#endif
