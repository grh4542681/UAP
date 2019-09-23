#ifndef __IO_SELECT_H__
#define __IO_SELECT_H__

#include "signal/process_signal_set.h"
#include "timer_time.h"

#include "io_return.h"
#include "io_fd.h"
#include "io_select_event.h"

#define SELECT_MAX_FD_SIZE (1024)

namespace io {

class Select {
public:
    Select(unsigned int item_size = SELECT_MAX_FD_SIZE);
    ~Select();

    IoRet AddEvent(FD& fd, int events);
    IoRet AddEvent(SelectEvent& event);
    IoRet ModEvent(FD& fd, int events);
    IoRet ModEvent(SelectEvent& event);
    IoRet DelEvent(FD& fd);

    std::vector<SelectEvent> Listen(timer::Time* overtime);
    std::vector<SelectEvent> Listen(process::signal::ProcessSignalSet* sigmask, timer::Time* overtime);
private:
    bool init_flag_;
    int efd_;
    unsigned int item_size_;
};

}

#endif
