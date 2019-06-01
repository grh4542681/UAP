#ifndef __PROCESS_PARENT_H__
#define __PROCESS_PARENT_H__

#include <string>

#include "time/vtime.h"
#include "socket/sock_pair.h"

#include "process_log.h"
#include "process_return.h"
#include "process_id.h"
#include "process_state.h"
#include "process_role.h"

#define ProcessParentSockFDIndex (0)

namespace process {

class ProcessParent {
public:
    ProcessParent();
    ProcessParent(std::string name, ProcessID& pid);
    ProcessParent(std::string name, ProcessID&& pid);
    ProcessParent(ProcessParent& other);
    ~ProcessParent();

    ipc::sock::SockPair& GetSockPair();

    ProcessParent& SetSockPair(ipc::sock::SockPair& pair);
    ProcessParent& SetSockPair(ipc::sock::SockPair&& pair);
    ProcessRet SetSendBlock(util::time::Time* overtime);
    ProcessRet SetRecvBlock(util::time::Time* overtime);
    ProcessRet SetNonBlock();

    ProcessRet Send();
    ProcessRet Recv();

private:
    ProcessID       pid_;
    std::string     name_;

    bool init_flag_;
    ipc::sock::SockPair pair_;
};

}

#endif
