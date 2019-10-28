#ifndef __PROCESS_GROUP_TIMER_H__
#define __PROCESS_GROUP_TIMER_H__

#include <string>
#include <functional>

#include "io_select_item.h"

#include "timer_return.h"
#include "timer_log.h"
#include "timer_fd.h"

namespace process::group {

template < typename K >
class ProcessGroupTimer {
public:
    class SelectItem : public io::SelectItem {
    public:
        SelectItem() : io::SelectItem() { } 
        SelectItem(ProcessGroupTimer* timerr) : io::SelectItem(timerr->GetTimerFD()) {
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
            ProcessRet ret = ProcessRet::SUCCESS;
            if (events & io::SelectEvent::Input) {
                if (InputFunc) {
                    ret = InputFunc(this);
                } else {
                    ret = _default_input_callback_func();
                }
                if (ret != ProcessRet::SUCCESS) {
                    return io::IoRet::IO_EINPUTCB;
                }
                printf("-------timer-----\n");
                events |= ~io::SelectEvent::Input;
            }
            if (events & io::SelectEvent::Output) {
                if (OutputFunc) {
                    ret = OutputFunc(this);
                    if (ret != ProcessRet::SUCCESS) {
                        return io::IoRet::IO_EOUTPUTCB;
                    }
                } else {
                }
                events |= ~io::SelectEvent::Output;
            }
            if (events & io::SelectEvent::Error) {
                if (ErrorFunc) {
                    ret = ErrorFunc(this);
                    if (ret != ProcessRet::SUCCESS) {
                        return io::IoRet::IO_EERRCB;
                    }
                } else {
                }
                events |= ~io::SelectEvent::Error;
            }
            return io::IoRet::SUCCESS;
        }

        std::function<ProcessRet(const K&, SelectItem*)> InputFunc;
        std::function<ProcessRet(const K&, SelectItem*)> OutputFunc;
        std::function<ProcessRet(const K&, SelectItem*)> ErrorFunc;

        ProcessGroupTimer* GetProcessGroupTimer() {
            return timerr_;
        }
    private:
        ProcessGroupTimer* timerr_;
        ProcessRet _default_input_callback_func() {
            printf("default i callback\n");
            return ProcessRet::SUCCESS;
        }
        ProcessRet _default_output_callback_func(SelectItem* select_item) {
            printf("default o callback\n");
            return ProcessRet::SUCCESS;
        }
        ProcessRet _default_error_callback_func(SelectItem* select_item) {
            printf("default e callback\n");
            return ProcessRet::SUCCESS;
        }
    };

public:
    ProcessGroupTimer();
    ProcessGroupTimer(timer::TimerFD& timer_fd);
    ProcessGroupTimer(int flag);
    ProcessGroupTimer(int flag, timer::Time& trigger_time, timer::Time& interval_time);
    ~ProcessGroupTimer();

    timer::TimerFD& GetTimerFD();
    SelectItem& GetSelectItem();
private:
    timer::TimerFD timer_fd_;
    SelectItem select_item_;
private:
    ProcessGroupTimer(ProcessGroupTimer& other);
    const ProcessGroupTimer& operator=(const ProcessGroupTimer& other);

};

}

#endif
