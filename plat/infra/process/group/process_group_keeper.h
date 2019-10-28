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
#include "process_group_timer.h"
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

    std::map<ProcessID, ProcessGroupWorker*>& GetGroupWorkers() {
        return worker_;
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
    ProcessGroupTimer<ProcessGroupKeeper<F, Args...>>* keep_timer_ = NULL;

    io::AutoSelect select_;

private:
    ProcessGroupKeeper(ProcessGroupKeeper& other);
    ProcessRet _group_init() {
        keep_timer_ = mempool::MemPool::getInstance()->Malloc<ProcessGroupTimer<ProcessGroupKeeper<F, Args...>>>(
                        this,
                        timer::TimerFD::Flag::Monotonic|timer::TimerFD::Flag::Nonblock,
                        timer::Time().SetTime(1, timer::Unit::Second),
                        timer::Time().SetTime(5, timer::Unit::Second));

        keep_timer_->GetSelectItem().GetSelectEvent().SetEvent(io::SelectEvent::Input);
        keep_timer_->GetSelectItem().InputFunc = &ProcessGroupKeeper<F, Args...>::keep_timer_callback;
        select_.AddSelectItem<typename ProcessGroupTimer<ProcessGroupKeeper<F, Args...>>::SelectItem>(keep_timer_->GetSelectItem());
        keep_timer_->GetTimerFD().Start();

        for (int loop = 0; loop < size_; loop++){
            _create_worker();
        }
        return ProcessRet::SUCCESS;
    }

    ProcessRet keep_timer_callback(typename ProcessGroupTimer<ProcessGroupKeeper<F, Args...>>::SelectItem* item) {
        printf("wowowowwowowowowwo\n");
        uint64_t count;
        item->GetProcessGroupTimer()->GetTimerFD().Read(&count, sizeof(uint64_t));
        printf("%d read size  --  %d\n",sizeof(uint64_t),count);
        printf("worker size [%d]\n", worker_.size());
        return ProcessRet::SUCCESS;
    }

    ProcessRet _create_worker() {
        auto child_ret = ptemp_.Run();
        ProcessRet ret = std::get<const ProcessRet>(child_ret);
        if (ret != ProcessRet::SUCCESS) {
            return ret;
        }
        ProcessID pid = std::get<const ProcessID>(child_ret);
        ProcessChild* child = ProcessInfo::getInstance()->GetChildProcess(pid);
        if (!child) {
            return ProcessRet::PROCESS_ENOCHILD;
        }
        ProcessGroupWorker* worker = mempool::MemPool::getInstance()->Malloc<ProcessGroupWorker>(pid, child->GetFD());
        if (!worker) {
            return ProcessRet::EMALLOC;
        }
        worker_.insert({pid, worker});
        return ProcessRet::SUCCESS;
    }

};

}

#endif
