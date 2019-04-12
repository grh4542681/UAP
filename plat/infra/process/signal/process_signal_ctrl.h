#ifndef __PROCESS_SIGNAL_CTRL_H__
#define __PROCESS_SIGNAL_CTRL_H__

#include <map>

#include "mempool.h"

#include "process_return.h"
#include "process_signal.h"
#include "process_signal_set.h"
#include "process_signal_action.h"
#include "process_signal_mask_type.h"

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
    ProcessRet MaskReplace();
    ProcessRet MaskReplace(ProcessSignalSet& set);
    ProcessRet MaskReplace(ProcessSignalSet& new_set, ProcessSignalSet& old_set);
    ProcessRet UnMask();
    ProcessRet UnMask(ProcessSignalSet& set);
    ProcessRet UnMask(ProcessSignalSet& new_set, ProcessSignalSet& old_set);
    ProcessRet MaskRevert();

    static ProcessSignalCtrl* getInstance();
private:
    ProcessSignalCtrl();
    ~ProcessSignalCtrl();

    mempool::MemPool* mempool_;
    std::map<ProcessSignal, ProcessSignalAction> register_map_;
    std::map<ProcessSignal, ProcessSignalAction> last_register_map_;

    ProcessSignalSet mask_set_;
    ProcessSignalSet last_mask_set_;

    static ProcessSignalCtrl* pInstance;

    ProcessRet _register_signal(ProcessSignal& sig, ProcessSignalAction& new_action, ProcessSignalAction& old_action);
    ProcessRet _mask_signal(SignalMaskType how, ProcessSignalSet& new_set, ProcessSignalSet& old_set);
};

}

#endif
