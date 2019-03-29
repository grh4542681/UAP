#ifndef __PROCESS_INFO_H__
#define __PROCESS_INFO_H__

namespace process {

class ProcessInfo {
public:
    static ProcessInfo* getInstance();
private:
    ProcessInfo();
    ~ProcessInfo();

    static ProcessInfo* pInstance;
};

};

#endif
