#ifndef __PROCESS_SIGNAL_ACTION_H__
#define __PROCESS_SIGNAL_ACTION_H__

#include "process_signal_set.h"

namespace process::signal {

class ProcessSignalCtrl;

class ProcessSignalAction {
public:
    friend class ProcessSignal;
    typedef void (*SignalCallback)(int);
    typedef void (*SignalCallback2)(int, siginfo_t*, void*);
public:
    ProcessSignalAction();
    ProcessSignalAction(const ProcessSignalAction& other);
    ~ProcessSignalAction();

    ProcessSignalAction& operator=(const ProcessSignalAction& other);

    void SetCallback(SignalCallback callback);
    void SetCallback(SignalCallback2 callback);
    void SetMaskset(ProcessSignalSet& set);
private:
    ProcessSignalAction(struct sigaction* action);
    struct sigaction action_;
};

}

#endif
