#ifndef __PROCESS_SIGNAL_H__
#define __PROCESS_SIGNAL_H__

#include <string>

namespace process::signal {

class ProcessSignal {
public:
    friend class ProcessSignalSet;
    friend class ProcessSignalCtrl;
public:
    ProcessSignal();
    ProcessSignal(int sig);
    ProcessSignal(const ProcessSignal& other);
    ~ProcessSignal();

    ProcessSignal& operator= (const ProcessSignal& other);
private:
    int sig_;
    std::string sig_name_;
};

}

#endif
