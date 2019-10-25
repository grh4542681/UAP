#ifndef __TIMER_TIMER_H__
#define __TIMER_TIMER_H__

#include <string>
#include <functional>

#include "io_select_item.h"

#include "timer_return.h"
#include "timer_log.h"
#include "timer_fd.h"

namespace timer {

class Timer {
public:
    class SelectItem : public io::SelectItem {
    public:
        SelectItem() : io::SelectItem() { } 
        SelectItem(Timer* timerr) : io::SelectItem(timerr->GetTimerFD()) {
            timerr_ = timerr;
        }   
        SelectItem(SelectItem& other): io::SelectItem(other) {
            timerr_ = other.timerr_;
            InputFunc = other.InputFunc;
            OutputFunc = other.OutputFunc;
            ErrorFunc = other.ErrorFunc;
        }   
        ~SelectItem() { } 

        SelectItem& operator=(SelectItem&& other) {
            io::SelectItem::operator=(other);
            timerr_ = other.timerr_;
            InputFunc = other.InputFunc;
            OutputFunc = other.OutputFunc;
            ErrorFunc = other.ErrorFunc;
            return *this;
        }

        io::IoRet Callback(int events) {
            TimerRet ret = TimerRet::SUCCESS;
            if (events & io::SelectEvent::Input) {
                if (InputFunc) {
                    ret = InputFunc(this);
                } else {
                    ret = _default_input_callback_func();
                }
                if (ret != TimerRet::SUCCESS) {
                    return io::IoRet::IO_EINPUTCB;
                }
                printf("-------timer-----\n");
                events |= ~io::SelectEvent::Input;
            }
            if (events & io::SelectEvent::Output) {
                if (OutputFunc) {
                    ret = OutputFunc(this);
                    if (ret != TimerRet::SUCCESS) {
                        return io::IoRet::IO_EOUTPUTCB;
                    }
                } else {
                }
                events |= ~io::SelectEvent::Output;
            }
            if (events & io::SelectEvent::Error) {
                if (ErrorFunc) {
                    ret = ErrorFunc(this);
                    if (ret != TimerRet::SUCCESS) {
                        return io::IoRet::IO_EERRCB;
                    }
                } else {
                }
                events |= ~io::SelectEvent::Error;
            }
            return io::IoRet::SUCCESS;
        }

        std::function<TimerRet(SelectItem*)> InputFunc;
        std::function<TimerRet(SelectItem*)> OutputFunc;
        std::function<TimerRet(SelectItem*)> ErrorFunc;

        Timer* GetTimer() {
            return timerr_;
        }
    private:
        Timer* timerr_;
        TimerRet _default_input_callback_func() {
            printf("default i callback\n");
            return TimerRet::SUCCESS;
        }
        TimerRet _default_output_callback_func(SelectItem* select_item) {
            printf("default o callback\n");
            return TimerRet::SUCCESS;
        }
        TimerRet _default_error_callback_func(SelectItem* select_item) {
            printf("default e callback\n");
            return TimerRet::SUCCESS;
        }
    };

public:
    Timer();
    Timer(TimerFD& timer_fd);
    Timer(int flag);
    Timer(int flag, Time& trigger_time, Time& interval_time);
    ~Timer();

    TimerFD& GetTimerFD();
    SelectItem& GetSelectItem();
private:
    TimerFD timer_fd_;
    SelectItem select_item_;
private:
    Timer(Timer& other);
    const Timer& operator=(const Timer& other);

};

}

#endif
