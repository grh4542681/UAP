#ifndef __TIMER_FD_H__
#define __TIMER_FD_H__

namespace timer {

class TimerFD : public io::FD {
public:
    TimerFD();
    TimerFD(unsigned int fd, bool auto_close = false);
    TimerFD(TimerFD& other);
    ~TimerFD();

    //Inherited from class FD.
    ret::Return SetFD(unsigned int fd, bool auto_close);
    ret::Return Dup(io::FD& new_fd);
    io::FD* Clone();
    void Close();
    size_t Write(const void* data, size_t datalen);
    size_t Read(void* data, size_t datalen);

public:
    static TimerFD CreateTFD();
}

}

#endif
