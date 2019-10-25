#include "timer_timer.h"

namespace timer {

Timer::Timer(TimerFD& timer_fd)
{
    timer_fd_ = timer_fd;
    select_item_ = SelectItem(this);
}

Timer::Timer(int flag)
{
    timer_fd_ = TimerFD(flag);
    select_item_ = SelectItem(this);
}

Timer::Timer(int flag, Time& trigger_time, Time& interval_time)
{
    timer_fd_ = TimerFD(flag, trigger_time, interval_time);
    select_item_ = SelectItem(this);
}

Timer::~Timer()
{

}

TimerFD& Timer::GetTimerFD()
{
    return timer_fd_;
}

Timer::SelectItem& Timer::GetSelectItem()
{
    return select_item_;
}

}
