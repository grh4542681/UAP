#ifndef __IO_FD_H__
#define __IO_FD_H__

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "mempool.h"

#include "io_return.h"

namespace io {

class FD {
public:
    FD() {
        fd_ = 0;
        init_flag_ = false;
        auto_close_ = false;
    }
    FD(unsigned int fd, bool auto_close) : fd_(fd), auto_close_(auto_close){
        init_flag_ = false;
    }
    FD(const FD& other) {
        if (fd_ > 0 && init_flag_ && auto_close_) {
            Close();
            fd_ = 0;
        }
        fd_ = other.fd_;
        auto_close_ = other.auto_close_;
        init_flag_ = other.init_flag_;
    }
    virtual ~FD() {}

    const FD& operator=(const FD& other) {
        if (fd_ > 0 && init_flag_ && auto_close_) {
            Close();
            fd_ = 0;
        }
        fd_ = other.fd_;
        auto_close_ = other.auto_close_;
        init_flag_ = other.init_flag_;
        return *this;
    }

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

    virtual ret::Return SetFD(unsigned int fd, bool auto_close) {
        if (fd_ > 0 && init_flag_ && auto_close_) {
            Close();
            fd_ = 0;
        }
        struct stat fd_stat;
        if (fstat(fd, &fd_stat)) {
            this->init_flag_ = false;
            return errno;
        }
        fd_ = fd;
        auto_close_ = auto_close;
        init_flag_ = true;
        return IoRet::SUCCESS;
    }

    virtual ret::Return Dup(FD& new_fd) {
        int fd = dup(fd_);
        if (fd < 0) {
            return errno;
        } else {
            new_fd.SetFD(fd, auto_close_);
            return IoRet::SUCCESS;
        }
    }

    virtual void Close() {
        close(fd_);
    }

    virtual FD* Clone() = 0;
    virtual size_t Write(const void* data, size_t datalen) = 0;
    virtual size_t Read(void* data, size_t datalen) = 0;
protected:
    unsigned int fd_ = 0;
    bool auto_close_ = false;
    bool init_flag_ = false;
};

}

#endif
