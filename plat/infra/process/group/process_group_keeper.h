#ifndef __PROCESS_GROUP_KEEPER_H__
#define __PROCESS_GROUP_KEEPER_H__

#include <string>
#include <utility>
#include <tuple>
#include <map>

#include "io_auto_select.h"
#include "io_select_item_template.h"
#include "timer_timer.h"

#include "process_id.h"
#include "process_group_worker.h"
#include "process_group_worker_template.h"
#include "process_group_worker_selectitem.h"

namespace process::group {

template < typename F, typename ... Args >
class ProcessGroupKeeper {
public:
    ProcessGroupKeeper(std::string name, int size, std::string config_filename, F worker, Args&& ... args) :
                    worker_temp_(name + ":worker", config_filename, worker, std::forward<Args>(args)...) {
        name_ = name;
        size_ = size;
    }
    ~ProcessGroupKeeper() {

    }

    std::map<ProcessID, ProcessGroupWorker>& GetGroupWorkers() {
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

    ProcessGroupWorkerTemplate<F, Args...> worker_temp_;
    std::map<ProcessID, ProcessGroupWorker> worker_;
    io::AutoSelect select_;

private:
    ProcessGroupKeeper(ProcessGroupKeeper& other);
    ProcessRet _group_init() {
        io::SelectItemTemplate<ProcessGroupKeeper<F, Args...>> keep_timer(
                        this, timer::TimerFD(
                        timer::TimerFD::Flag::Monotonic|timer::TimerFD::Flag::Nonblock,
                        timer::Time().SetTime(1, timer::Unit::Second),
                        timer::Time().SetTime(5, timer::Unit::Second)));

        keep_timer.GetSelectEvent().SetEvent(io::SelectEvent::Input);
        keep_timer.InputFunc = &ProcessGroupKeeper<F, Args...>::keep_timer_callback;
        select_.AddSelectItem<io::SelectItemTemplate<ProcessGroupKeeper<F, Args...>>>(keep_timer);
        keep_timer.template GetFd<timer::TimerFD>().Start();

        for (int loop = 0; loop < size_; loop++){
            _create_worker();
        }
        return ProcessRet::SUCCESS;
    }

    ProcessRet _create_worker() {
        auto child_ret = worker_temp_.Run();
        ProcessRet ret = std::get<const ProcessRet>(child_ret);
        if (ret != ProcessRet::SUCCESS) {
            return ret;
        }
        ProcessID pid = std::get<const ProcessID>(child_ret);
        ProcessChild* child = ProcessInfo::getInstance()->GetChildProcess(pid);
        if (!child) {
            return ProcessRet::PROCESS_ENOCHILD;
        }

        ProcessGroupWorkerSelectItem<ProcessGroupKeeper<F, Args...>> worker_selectitem(
                        this, pid, child->GetFD());
        worker_selectitem.GetSelectEvent().SetEvent(io::SelectEvent::Input);
        worker_selectitem.InputFunc = &ProcessGroupKeeper<F, Args...>::worker_input_callback;
        select_.AddSelectItem<ProcessGroupWorkerSelectItem<ProcessGroupKeeper<F, Args...>>>(worker_selectitem);

        ProcessGroupWorker worker(pid, child->GetFD());
        worker_.insert({pid, worker});
        return ProcessRet::SUCCESS;
    }

    io::IoRet keep_timer_callback(io::SelectItemTemplate<ProcessGroupKeeper<F, Args...>>* item) {
        uint64_t count;
        item->template GetFd<timer::TimerFD>().Read(&count, sizeof(uint64_t));
        printf("%lu read size  --  %lu\n",sizeof(uint64_t),count);
        printf("worker size [%ld]\n", worker_.size());
        return io::IoRet::SUCCESS;
    }

    io::IoRet worker_input_callback(io::SelectItemTemplate<ProcessGroupKeeper<F, Args...>>* item) {
        auto worker_item = dynamic_cast<ProcessGroupWorkerSelectItem<ProcessGroupKeeper<F, Args...>>*>(item);
        ProcessID& pid = worker_item->GetPid();
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        worker_item->template GetFd<sock::SockFD>().Read(buf,sizeof(buf));
        printf("pid:%d recv:%s\n",pid.GetID(),buf);
        return io::IoRet::SUCCESS;
    }


};

}

#endif
