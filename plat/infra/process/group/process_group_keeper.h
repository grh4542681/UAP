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
        ProcessRet ret;
        if ((ret = _group_init()) != ProcessRet::SUCCESS) {
            return ret;
        }
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
    int size_ = 0;
    int cursize = 0;
    bool init_flag_ = false;
    bool auto_size_flag_ = false;

    ProcessGroupWorkerTemplate<F, Args...> ptemp_;
    std::map<ProcessID, ProcessGroupWorker*> worker_;
    timer::Timer* keep_timer_ = NULL;

    io::AutoSelect select_;

private:
    ProcessGroupKeeper(ProcessGroupKeeper& other);
    ProcessRet _group_init() {
        timer::Timer keep_timer_ = mempool::MemPool::getInstance()->Malloc<timer::Timer>(
                        timer::TimerFD::Flag::Monotonic|timer::TimerFD::Flag::Nonblock,
                        timer::Time().SetTime(0, timer::Unit::Second),
                        timer::Time().SetTime(10, timer::Unit::Second));

        keep_timer_->GetSelectItem().GetSelectEvent().SetEvent(io::SelectEvent::Input);
        keep_timer_->GetSelectItem().InputFunc = keep_timer_callback;
        select_.AddSelectItem<timer::Timer::SelectItem>(keep_timer_->GetSelectItem());
        keep_timer_->GetTimerFD().Start();

        for (int loop = 0; loop < size_; loop++){
            ptemp_.Run();
        }
        return ProcessRet::SUCCESS;
    }

    static timer::TimerRet keep_timer_callback(timer::Timer::SelectItem* item) {
        printf("wowowowwowowowowwo\n");
        uint64_t count;
        item->GetTimer()->GetTimerFD().Read(&count, sizeof(uint64_t));
        printf("%d read size  --  %d\n",sizeof(uint64_t),count);
        return timer::TimerRet::SUCCESS;
    }

};

}

#endif
