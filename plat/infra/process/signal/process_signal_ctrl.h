#ifndef __PROCESS_SIGNAL_CTRL_H__
#define __PROCESS_SIGNAL_CTRL_H__

#include <map>

#include "mempool.h"

#include "process_return.h"
#include "process_signal.h"
#include "process_signal_set.h"
#include "process_signal_action.h"

namespace process::signal {

class ProcessSignalCtrl {
public:
    ProcessRet Register(ProcessSignal& sig, ProcessSignalAction& action);
    ProcessRet Register(ProcessSignal& sig, ProcessSignalAction& new_action, ProcessSignalAction& old_action);
    ProcessRet UnRegister();
    ProcessRet UnRegister(ProcessSignal& sig);
    ProcessRet UnRegister(ProcessSignal& sig, ProcessSignalAction& old_action);
    ProcessRet Revert();
    ProcessRet Revert(ProcessSignal& sig);
    
    ProcessRet Mask();
    ProcessRet Mask(ProcessSignalSet& set);
    ProcessRet Mask(ProcessSignalSet& new_set, ProcessSignalSet& old_set);
    ProcessRet MaskRevert();

    static ProcessSignalCtrl* getInstance();
private:
    ProcessSignalCtrl();
    ~ProcessSignalCtrl();

    mempool::MemPool* mempool_;
    std::map<ProcessSignal*, ProcessSignalAction*> register_map_;
    std::map<ProcessSignal*, ProcessSignalAction*> last_register_map_;

    static ProcessSignalCtrl* pInstance;

    ProcessRet _register_signal(int sig, struct sigaction* new_action, struct sigaction* old_action);
};

}

#endif
