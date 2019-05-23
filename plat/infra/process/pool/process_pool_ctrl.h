#ifndef __PROCESS_POOL_CTRL_H__
#define __PROCESS_POOL_CTRL_H__

#include <string>

namespace process::pool {

class ProcessPoolCtrl {
public:
    ProcessPoolCtrl(std::string name);
    ~ProcessPoolCtrl();

    ProcessRet Create(size_t min_size, size_t max_size);
    ProcessRet Destroy();

    ProcessRet PushJob(ProcessPoolCtrlJob* job);
private:
    std::string name_;
    size_t min_size_;
    size_t max_size_;
    size_t working_size_;
    bool init_flag_;
    bool auto_size_flag_;



};

}

#endif
