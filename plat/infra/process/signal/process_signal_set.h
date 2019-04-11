#ifndef __PROCESS_SIGNAL_SET_H__
#define __PROCESS_SIGNAL_SET_H__

#include "signal.h"

#include "process_return.h"
#include "process_signal.h"

namespace process::signal {

class ProcessSignalCtrl;
class ProcessSignalAction;

class ProcessSignalSet {
public:
    friend class ProcessSignalAction;
    friend class ProcessSignalCtrl;
public:
    ProcessSignalSet();
    ProcessSignalSet(const ProcessSignalSet& other);
    ~ProcessSignalSet();

    ProcessSignalSet& operator= (const ProcessSignalSet& other);

    ProcessRet AddSig(ProcessSignal& sig);
    ProcessRet AddAll();
    ProcessRet DelSig(ProcessSignal& sig);
    ProcessRet DelAll();
    bool HasSig(ProcessSignal& sig);

private:
    sigset_t set_;
};

}

#endif
