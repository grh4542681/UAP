#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <string>

#include "time/vtime.h"

#include "process_return.h"
#include "process_info.h"

namespace process {

class Process {
public:
    static ProcessRet SetProcName(std::string name);

    static ProcessRet SendToParent(char* msg, unsigned int* msglen, util::time::Time* overtime);
    static ProcessRet RecvFromParent(char* msg, unsigned int* msglen, util::time::Time* overtime);

    static ProcessRet RegisterCommonSigChld();
private:
    Process();
    ~Process();
};

}

#endif
