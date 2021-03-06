#ifndef __IO_FD_H__
#define __IO_FD_H__

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "mempool_alloctor.h"

#include "io_return.h"

namespace io {

/**
* @brief - Base file descriptor class
*/
class FD {
public:
    /**
    * @brief FD - Default consturctor
    */
    FD() {
        fd_ = 0;
        init_flag_ = false;
        auto_close_ = false;
    }
    /**
    * @brief FD - Consturctor
    *
    * @param [fd] - Linux file descriptor
    * @param [auto_close] - Auto close flag
    */
    FD(unsigned int fd, bool auto_close = false) : fd_(fd), auto_close_(auto_close){
        struct stat fd_stat;
        if (fstat(fd, &fd_stat)) {
            fd_ = -1;
            this->init_flag_ = false;
        }
        auto_close_ = false;
        init_flag_ = false;
    }
    /**
    * @brief FD - Copy constructor
    *
    * @param [other] -  Other instance
    */
    FD(FD& other) {
        if (fd_ > 0 && init_flag_ && auto_close_) {
            Close();
            fd_ = 0;
        }
        fd_ = other.fd_;
        auto_close_ = other.auto_close_;
        init_flag_ = other.init_flag_;
    }
    /**
    * @brief FD - Copy constructor
    *
    * @param [other] -  Other instance
    */
    FD(FD&& other) {
        if (fd_ > 0 && init_flag_ && auto_close_) {
            Close();
            fd_ = 0;
        }
        fd_ = other.fd_;
        auto_close_ = other.auto_close_;
        init_flag_ = other.init_flag_;
    }
    /**
    * @brief FD - Copy constructor
    *
    * @param [other] -  Other instance
    */
    FD(const FD& other) {
        if (fd_ > 0 && init_flag_ && auto_close_) {
            Close();
            fd_ = 0;
        }
        fd_ = other.fd_;
        auto_close_ = other.auto_close_;
        init_flag_ = other.init_flag_;
    }
    /**
    * @brief FD - Copy constructor
    *
    * @param [other] -  Other instance
    */
    FD(const FD&& other) {
        if (fd_ > 0 && init_flag_ && auto_close_) {
            Close();
            fd_ = 0;
        }
        fd_ = other.fd_;
        auto_close_ = other.auto_close_;
        init_flag_ = other.init_flag_;
    }
    /**
    * @brief ~FD - Destructor
    */
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

    const FD& operator=(const FD&& other) {
        if (fd_ > 0 && init_flag_ && auto_close_) {
            Close();
            fd_ = 0;
        }
        fd_ = other.fd_;
        auto_close_ = other.auto_close_;
        init_flag_ = other.init_flag_;
        return *this;
    }

    bool operator==(const FD& other) const {
        return (fd_ == other.fd_);
    }
    bool operator==(const int& fd) const {
        return (fd_ == fd);
    }
/*
    bool operator<(const FD& other) const {
        return (fd_ < other.fd_);
    }
    bool operator<(const unsigned int& fd) const {
        return (fd_ < fd);
    }
*/
    bool GetAutoClose() {
        return auto_close_;
    }

    FD& SetAutoClose(bool flag) {
        auto_close_ = flag;
        return *this;
    }

    bool Initalize() const {
        return init_flag_;
    }

    bool Available() {
        return true;
    }

    int GetFD() const {
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
        if (init_flag_ && auto_close_){
            close(fd_);
        }
    }

    virtual FD* Clone() {
        return alloc_.Allocate<FD>(*this);
    }
    virtual ssize_t Write(const void* data, size_t datalen) {
        return 0;
    }
    virtual ssize_t Read(void* data, size_t datalen) {
        return 0;
    }
protected:
    int fd_ = 0;
    bool auto_close_ = false;
    bool init_flag_ = false;
    mempool::MempoolAlloctor alloc_;
};

bool operator<(const FD& a, const int b);
bool operator<(const int a, const FD& b);
bool operator<(const FD& a, const FD& b);

}

#endif
