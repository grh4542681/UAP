#ifndef __PROCESS_ID_H__
#define __PROCESS_ID_H__

#include <sys/types.h>

namespace process {

class ProcessID {
public:
    typedef pid_t ProcessID_t;
public:
    ProcessID();
    ProcessID(ProcessID& other);
    ProcessID(const ProcessID& other);
    ~ProcessID();

    ProcessID& operator=(ProcessID other);

    bool operator==(ProcessID& other);
    bool operator==(const ProcessID& other);
    bool operator<(ProcessID& other);
    bool operator<(const ProcessID& other);
    bool operator>(ProcessID& other);
    bool operator>(const ProcessID& other);

    ProcessID& SetID(ProcessID_t pid);
    ProcessID_t GetID();

    static ProcessID GetProcessID();
    static ProcessID GetProcessParentID();
private:
    ProcessID_t pid_;
};

bool operator<(const ProcessID& a, const ProcessID& b);

}

#endif
