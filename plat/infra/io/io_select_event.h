#ifndef __IO_SELECT_EVENT_H__
#define __IO_SELECT_EVENT_H__

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
    SelectEvent(FD& fd, int events) : fd_(fd), events_(events) { }
    SelectEvent(SelectEvent& other) {
        fd_ = other.fd_;
        events_ = other.events_;
    }
    ~SelectEvent() { }

    SelectEvent& operator=(SelectEvent& other) {
        fd_ = other.fd_;
        events_ = other.events_;
        return *this;
    }
    SelectEvent& operator+(int event) {
        events_ |= event;
        return *this;
    }
    SelectEvent& operator-(int event) {
        events_ &= event;
        return *this;
    }

    FD& GetFd() { return fd_; };
    int GetEvents() { return events_; };

    SelectEvent& SetEvent(int events) {
        events_ = events;
        return *this;
    }

    bool HasInput() { return (events_ & SelectEvent::Input); }
    bool HasOutput() { return (events_ & SelectEvent::Output); }
    bool HasError() { return (events_ & SelectEvent::Error); }

private:
    FD fd_;
    int events_;
};

}

#endif
