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
    ProcessChild(std::string name, ProcessID&& pid);
    ProcessChild(ProcessChild& other);
    ~ProcessChild();

    ProcessID& GetPid();
    std::string GetName();
    ProcessRole& GetRole();
    ProcessState& GetState();
    void (*GetDeadCallback())(int*);
    ipc::sock::SockPair& GetSockPair();

    ProcessChild& SetState(ProcessState state);
    ProcessChild& SetDeadCallback(void (*dead_callback)(int*));
    ProcessChild& SetSockPair(ipc::sock::SockPair& pair);
    ProcessChild& SetSockPair(ipc::sock::SockPair&& pair);

    ProcessRet SetSendBlock(util::time::Time* overtime);
    ProcessRet SetRecvBlock(util::time::Time* overtime);
    ProcessRet SetNonBlock();

    ProcessRet Send();
    ProcessRet Recv();

private:
    ProcessID       pid_;
    std::string     name_;
    ProcessRole     role_;
    ProcessState    state_;

    bool init_flag_;
    ipc::sock::SockPair pair_;
    void (*dead_callback_)(int*);
};

}

#endif
