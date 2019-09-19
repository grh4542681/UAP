#include "timer_fd.h"

namespace timer {

TimerFD::TimerFD() : FD()
{

}

TimerFD::TimerFD(unsigned int fd, bool auto_close = false) : FD(fd, auto_close)
{
    int temp_errno = 0;
    struct stat fd_stat;
    if (fstat(fd, &fd_stat)) {
        temp_errno = errno;
        printf("%s", strerror(temp_errno));
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


}
