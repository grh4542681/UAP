#ifndef __PROCESS_POOL_JOB_H__
#define __PROCESS_POOL_JOB_H__

#include <string>

namespace process::pool {

enum class ProcessPoolTaskState {
    READY,
    WAIT,
    RUNNING,
    ERROR,
    SUCCESS,
};

class ProcessPoolTask {
public:
    ProcessPoolTask(std::string name);
    ~ProcessPoolTask();

    ProcessRet Run();

protected:
    std::string name_;
    std::string describe_;
    std::string message_;
    ProcessPoolTaskState state_;

    util::time::Time create_time_;
    util::time::Time execute_time_;
    util::time::Time finish_time_;

    virtual ProcessRet task_main_() { return ProcessRet::ESUBCLASS; }
};

}

#endif
