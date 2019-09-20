#ifndef __TIMER_FD_H__
#define __TIMER_FD_H__

#include "timer_return.h"

namespace timer {

class TimerFD : public io::FD {
public:
    enum Flag {
        CloseExec,
        Nonblock,
        Relative,
    };
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

    Time& GetTriggerTime();
    Time& GetIntervalTime();
    int GetTriggerCounts();

    TimerRet Start();
    TimerRet Stop();

public:
    static const int CLOEXEC = { EFD_CLOEXEC };
    static const int NONBLOCK = { EFD_NONBLOCK };

    static TimerFD CreateTFD(int flag, Time& trigger_time, Time& interval_time);

private:
    Time trigger_time_;
    Time interval_time_;
}

}

#endif
