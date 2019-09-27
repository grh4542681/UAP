#ifndef __TIMER_FD_H__
#define __TIMER_FD_H__

#include "io_fd.h"

#include "timer_return.h"
#include "timer_time.h"

namespace timer {

class TimerFD : public io::FD {
public:
    enum Flag {
        Realtime,
        Monotonic,
        CloseExec,
        Nonblock,
        Relative,
        Absolute,
    };
public:
    TimerFD();
    TimerFD(int flag, Time& trigger_time, Time& interval_time);
    TimerFD(unsigned int fd, bool auto_close = false);
    TimerFD(TimerFD& other);
    ~TimerFD();

    //Inherited from class FD.
    ret::Return SetFD(unsigned int fd, bool auto_close);
    ret::Return Dup(io::FD& new_fd);
    io::FD* Clone();
    void Close();
    ssize_t Write(const void* data, size_t datalen);
    ssize_t Read(void* data, size_t datalen);

    Time& GetTriggerTime();
    Time& GetIntervalTime();
    int GetTriggerCounts();

    TimerRet Start();
    TimerRet Start(int flag, Time& trigger_time, Time& interval_time);
    TimerRet Stop();

private:
    bool first_start_ = true;
    int flag_ = 0;
    Time trigger_time_;
    Time interval_time_;
};

}

#endif
