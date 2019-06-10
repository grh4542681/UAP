#ifndef __BASE_IO_H__
#define __BASE_IO_H__

#include "baseio_return.h"

namespace baseio {

class FD {
public:
    virtual unsigned int GetFD() {
        return fd_;
    }
    virtual BaseIORet SetFD(unsigned int fd, bool auto_close = true) {
        fd_ = fd;
        auto_close_ = auto_close;
        return BaseIORet::SUCCESS;
    }

    virtual void Close();
    virtual size_t Send(const void* data, size_t datalen);
    virtual size_t Recv(void* data, size_t datalen);
protected:
    unsigned int fd_;
    bool auto_close_;
}

}

#endif
