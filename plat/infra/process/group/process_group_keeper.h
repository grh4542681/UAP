#ifndef __PROCESS_GROUP_KEEPER_H__
#define __PROCESS_GROUP_KEEPER_H__

#include <string>
#include <utility>
#include <tuple>
#include <map>

#include "io_auto_select.h"
#include "timer_timer.h"

#include "process_id.h"
#include "process_group_worker.h"
#include "process_group_worker_template.h"

namespace process::group {

template < typename F, typename ... Args >
class ProcessGroupKeeper {
public:
    ProcessGroupKeeper(std::string name, int size, std::string config_filename, F worker, Args&& ... args) :
                    ptemp_(name + ":worker", config_filename, worker, std::forward<Args>(args)...) {
        name_ = name;
        size_ = size;
    }
    ~ProcessGroupKeeper() {

    }

    ProcessRet Run() {
        timer::Timer keep_timer(timer::TimerFD::Flag::Monotonic, timer::Time().SetTime(2, timer::Unit::Second), timer::Time().SetTime(2, timer::Unit::Second));

        keep_timer.GetSelectItem().GetSelectEvent().SetEvent(io::SelectEvent::Input);
        keep_timer.GetSelectItem().InputFunc = keep_timer_callback;
        select_.AddSelectItem<timer::Timer::SelectItem>(keep_timer.GetSelectItem());
        keep_timer.GetTimerFD().Start();

        for (int loop = 0; loop < size_; loop++){
            ptemp_.Run();
        }
        //return ProcessRet::SUCCESS;

        //ProcessRet ret;
        //if ((ret = _group_init()) != ProcessRet::SUCCESS) {
        //    return ret;
        //}
        select_.Listen(timer::Time());
        return ProcessRet::SUCCESS;
    }

    ProcessRet RunThread() {
        ProcessRet ret;
        if ((ret = _group_init()) != ProcessRet::SUCCESS) {
            return ret;
        }
        select_.ListenThread(timer::Time());
        return ProcessRet::SUCCESS;
    }

private:
    std::string name_;
    int size_;
    bool init_flag_;
    bool auto_size_flag_;

    ProcessGroupWorkerTemplate<F, Args...> ptemp_;
    std::map<ProcessID, ProcessGroupWorker*> worker_;

    io::AutoSelect select_;

    ProcessRet _group_init() {
        timer::Timer keep_timer(timer::TimerFD::Flag::Monotonic, timer::Time().SetTime(2, timer::Unit::Second), timer::Time().SetTime(2, timer::Unit::Second));

        keep_timer.GetSelectItem().GetSelectEvent().SetEvent(io::SelectEvent::Input);
        keep_timer.GetSelectItem().InputFunc = keep_timer_callback;
        select_.AddSelectItem<timer::Timer::SelectItem>(keep_timer.GetSelectItem());
        keep_timer.GetTimerFD().Start();

        for (int loop = 0; loop < size_; loop++){
            ptemp_.Run();
        }
        return ProcessRet::SUCCESS;
    }

    static timer::TimerRet keep_timer_callback(timer::Timer::SelectItem* item) {
        printf("wowowowwowowowowwo\n");
        int i;
        item->GetTimer()->GetTimerFD().Read(&i, sizeof(int));
        printf("read %d\n",i);
        return timer::TimerRet::SUCCESS;
    }

};

}

#endif
