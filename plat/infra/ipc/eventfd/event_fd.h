#ifndef __EVENT_FD_H__
#define __EVENT_FD_H__

#include <sys/eventfd.h>

#include "io_fd.h"

#include "ipc_return.h"

namespace ipc::eventfd {

class EventFD : public io::FD {
public:
    EventFD();
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

    //get & set
    bool IsCloexec();
    bool IsNonblock();
    bool IsSemaphore();
    void SetEfdFlag(int flag);

private:
    int efd_flag_ = { 0 };

public:
    static const int CLOEXEC = { EFD_CLOEXEC };
    static const int NONBLOCK = { EFD_NONBLOCK };
    static const int SEMAPHORE = { EFD_SEMAPHORE };

    static EventFD CreateEFD(int flag);
};

}

#endif
