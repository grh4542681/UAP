#ifndef __EVENT_FD_H__
#define __EVENT_FD_H__

#include <sys/eventfd.h>

#include "io_fd.h"

#include "ipc_return.h"

namespace ipc::eventfd {

class EventFD : public io::FD {
public:
    EventFD();
    EventFD(int flag);
    ~EventFD();

    IpcRet SetFD(unsigned int fd, bool auto_close);
    io::FD* Clone();
    void Close();
    size_t Write(const void* data, size_t datalen);
    size_t Read(void* data, size_t datalen);

    static const int CLOEXEC = { EFD_CLOEXEC };
    static const int NONBLOCK = { EFD_NONBLOCK };
    static const int SEMAPHORE = { EFD_SEMAPHORE };
};

}

#endif
