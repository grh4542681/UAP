#include <sys/timerfd.h>

#include "timer_fd.h"
#include "timer_log.h"

namespace timer {

TimerFD::TimerFD() : FD()
{

}

TimerFD(int flag, Time& trigger_time, Time& interval_time)
{
    auto_close = false;
    flag_ = flag;
    trigger_time_ = trigger_time;
    interval_time_ = interval_time;

    int clockid = 0;
    int flags = 0;

    if (flag_ & CLOCK_REALTIME) {
        clockid |= CLOCK_REALTIME;
    }
    if (flag_ & CLOCK_MONOTONIC) {
        clockid |= CLOCK_MONOTONIC;
    }
    if (flag_ & TFD_CLOEXEC) {
        flags |= TFD_CLOEXEC;
    }
    if (flag_ & TFD_NONBLOCK) {
        flags |= TFD_NONBLOCK;
    }

    fd_ = timerfd_create(clockid, flag_);
    if (fd_ <= 0) {
        TIMER_ERROR("Create timer fd error: %s", strerror(errno));
        init_flag_ = false;
    }
    init_flag_ = true;
}

TimerFD::TimerFD(unsigned int fd, bool auto_close = false) : FD(fd, auto_close)
{
    int temp_errno = 0;
    struct stat fd_stat;
    if (fstat(fd, &fd_stat)) {
        temp_errno = errno;
        TIMER_ERROR("%s", strerror(temp_errno));
        init_flag_ = false;
    }
    init_flag_ = true;
}

TimerFD::TimerFD(TimerFD& other) : FD(other)
{
    start_time_ = other.start_time_;
    inter_time_ = other.start_time_;
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
{}

Time& TimerFD::GetIntervalTime()
{}

int TimerFD::GetTriggerCounts()
{}


TimerRet TimerFD::Start();
TimerRet TimerFD::Stop();

}
