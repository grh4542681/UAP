#ifndef __IO_SELECT_EVENT_H__
#define __IO_SELECT_EVENT_H__

#include <utility>
#include <sys/epoll.h>

namespace io {

class SelectEvent {
public:
    const static int Input = EPOLLIN;
    const static int Output = EPOLLOUT;
    const static int Error = EPOLLERR;
    const static int Oneshot = EPOLLONESHOT;
public:
    SelectEvent() : events_(0) { }
    SelectEvent(const FD& fd, int events = 0) : events_(events) {
        fd_ = const_cast<FD&>(fd).Clone();
    }
    SelectEvent(const FD&& fd, int events = 0) : events_(events) {
        fd_ = const_cast<FD&>(fd).Clone();
    }
    SelectEvent(const SelectEvent& other) {
        if (other.fd_) {
            fd_ = other.fd_->Clone();
        }
        events_ = other.events_;
    }
    ~SelectEvent() {
        if (fd_) {
            mempool::MemPool::getInstance()->Free<FD>(fd_);
        }
    }

    SelectEvent& operator=(const SelectEvent& other) {
        if (fd_) {
            mempool::MemPool::getInstance()->Free<FD>(fd_);
            fd_ = NULL;
        }
        if (other.fd_) {
            fd_ = other.fd_->Clone();
        }
        events_ = other.events_;
        return *this;
    }
    SelectEvent& operator|(int event) {
        events_ |= event;
        return *this;
    }
    SelectEvent& operator&(int event) {
        events_ &= event;
        return *this;
    }

    FD& GetFd() { return *fd_; };
    FD* GetFdPointer() { return fd_; };
    int GetEvents() { return events_; };

    SelectEvent& SetEvent(int events) {
        events_ = events;
        return *this;
    }

    bool HasInput() { return (events_ & SelectEvent::Input); }
    bool HasOutput() { return (events_ & SelectEvent::Output); }
    bool HasError() { return (events_ & SelectEvent::Error); }
    bool HasOneshot() { return (events_ & SelectEvent::Oneshot); }

protected:
    FD* fd_ = NULL;
    int events_ = 0;
};

}

#endif
