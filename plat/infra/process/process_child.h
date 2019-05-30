#ifndef __PROCESS_CHILD_H__
#define __PROCESS_CHILD_H__

#include <string>

#include "time/vtime.h"
#include "socket/sock_pair.h"

#include "process_log.h"
#include "process_return.h"
#include "process_id.h"
#include "process_state.h"
#include "process_role.h"

#define ProcessChildSockFDIndex (1)

namespace process {

class ProcessChild {
public:
    ProcessChild();
    ProcessChild(ProcessChild& other);
    ~ProcessChild();

    ProcessChild& Enable();

    ProcessRet setSendBlock(util::time::Time* overtime);
    ProcessRet setRecvBlock(util::time::Time* overtime);
    ProcessRet setNonBlock();

    ProcessRet Send();
    ProcessRet Recv();

public:
    ProcessID       Pid;
    std::string     Name;
    std::string     ProcessPath;
    std::string     ProcessName;
    ProcessRole     Role;
    ProcessState    State;

private:
    bool init_flag_;
    ipc::sock::SockPair pair_;
    void (*dead_callback_)(int*);
};

}

#endif
