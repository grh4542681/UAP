#ifndef __IO_FD_H__
#define __IO_FD_H__

#include <unistd.h>

#include "io_return.h"

namespace io {

class FD {
public:
    FD() {
        fd_ = 0;
        init_flag_ = false;
        auto_close_ = false;
    }
    virtual ~FD() {}

    bool GetAutoClose() {
        return auto_close_;
    }

    void SetAutoClose(bool flag) {
        auto_close_ = flag;
    }

    bool IsFine() {
        return true;
    }

    int GetFD() {
        if (init_flag_) {
            return fd_;
        } else {
            return (-1);
        }
    }

    virtual FD* Clone() = 0;
    virtual void Close() = 0;
    virtual size_t Write(const void* data, size_t datalen) = 0;
    virtual size_t Read(void* data, size_t datalen) = 0;
protected:
    unsigned int fd_;
    bool auto_close_;
    bool init_flag_;
};

}

#endif
