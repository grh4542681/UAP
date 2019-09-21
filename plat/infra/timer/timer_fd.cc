#include <sys/timerfd.h>

#include "timer_fd.h"
#include "timer_log.h"

namespace timer {

TimerFD::TimerFD() : FD()
{

}

TimerFD::TimerFD(int flag, Time& trigger_time, Time& interval_time)
{
    first_start_ = true;
    auto_close_ = false;
    flag_ = flag;
    trigger_time_ = trigger_time;
    interval_time_ = interval_time;

    int clockid = 0;
    int flags = 0;

    if (flag_ & Flag::Realtime) {
        clockid |= CLOCK_REALTIME;
    }
    if (flag_ & Flag::Monotonic) {
        clockid |= CLOCK_MONOTONIC;
    }
    if (flag_ & Flag::CloseExec) {
        flags |= TFD_CLOEXEC;
    }
    if (flag_ & Flag::Nonblock) {
        flags |= TFD_NONBLOCK;
    }

    fd_ = timerfd_create(clockid, flag_);
    if (fd_ <= 0) {
        TIMER_ERROR("Create timer fd error: %s", strerror(errno));
        init_flag_ = false;
    }
    init_flag_ = true;
}

TimerFD::TimerFD(unsigned int fd, bool auto_close) : FD(fd, auto_close)
{
    int temp_errno = 0;
    struct stat fd_stat;
    if (fstat(fd, &fd_stat)) {
        temp_errno = errno;
        TIMER_ERROR("%s", strerror(temp_errno));
        init_flag_ = false;
    }
    init_flag_ = true;
    first_start_ = true;
}

TimerFD::TimerFD(TimerFD& other) : FD(other)
{
    first_start_  = other.first_start_;
    flag_ = other.flag_;
    trigger_time_ = other.trigger_time_;
    interval_time_ = other.interval_time_;
}

TimerFD::~TimerFD()
{
    if (init_flag_ && auto_close_) {
        close(fd_);
    }
}

ret::Return TimerFD::SetFD(unsigned int fd, bool auto_close)
{
    if (fd_ > 0 && init_flag_ && auto_close_) {
        close(fd_);
        fd_ = 0;
    }
    int temp_errno = 0;
    struct stat fd_stat;
    if (fstat(fd, &fd_stat)) {
        temp_errno = errno;
        TIMER_ERROR("%s", strerror(temp_errno));
        init_flag_ = false;
        return temp_errno;
    }
    fd_ = fd;
    init_flag_ = true;
    auto_close_ = auto_close;
    first_start_ = true;
    trigger_time_.SetTime(0, Unit::Second);
    interval_time_.SetTime(0, Unit::Second);
    return ret::Return::SUCCESS;
}

ret::Return TimerFD::Dup(io::FD& new_fd)
{

}

io::FD* TimerFD::Clone()
{
    return mempool::MemPool::getInstance()->Malloc<TimerFD>(*this);
}

void TimerFD::Close()
{
    close(fd_);
}

size_t TimerFD::Write(const void* data, size_t datalen)
{
    TIMER_ERROR("Timer fd not support write.");
    return 0;
}

size_t TimerFD::Read(void* data, size_t datalen)
{}

Time& TimerFD::GetTriggerTime()
{
    return trigger_time_;
}

Time& TimerFD::GetIntervalTime()
{
    return interval_time_;
}

int TimerFD::GetTriggerCounts()
{
    return 0;
}

TimerRet TimerFD::Start(int flag, Time& trigger_time, Time& interval_time)
{
    flag_ = flag;
    trigger_time_ = trigger_time;
    interval_time_ = interval_time;
    first_start_ = true;
    return Start();
}

TimerRet TimerFD::Start()
{
    int flags = 0;
    if (flag_ & Flag::Absolute) {
        flags |= TFD_TIMER_ABSTIME;
    }

    struct itimerspec itime;
    memset(&itime, 0x00, sizeof(struct itimerspec));

    if (first_start_) {
        first_start_ = false;
        trigger_time_.To(&itime.it_interval);
    }
    interval_time_.To(&itime.it_value);

    if (timerfd_settime(fd_, flags, &itime, NULL) < 0) {
        int tmp_errno = errno;
        TIMER_ERROR("Start timer error: %s", strerror(tmp_errno));
        return tmp_errno;
    }
    return TimerRet::SUCCESS;
}

TimerRet TimerFD::Stop()
{
    int flags = 0;
    if (flag_ & Flag::Absolute) {
        flags |= TFD_TIMER_ABSTIME;
    }

    struct itimerspec itime;
    memset(&itime, 0x00, sizeof(struct itimerspec));
    
    if (timerfd_settime(fd_, flags, &itime, NULL) < 0) {
        int tmp_errno = errno;
        TIMER_ERROR("Stop timer error: %s", strerror(tmp_errno));
        return tmp_errno;
    }
    return TimerRet::SUCCESS;
}


}
