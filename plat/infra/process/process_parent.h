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

class ProcessTemplate;

class ProcessParent {
public:
    friend class ProcessTemplate;
public:
    ProcessParent();
    ProcessParent(std::string name, ProcessID&& pid);
    ProcessParent(ProcessParent& other);
    ~ProcessParent();

    ProcessParent& setSockPair(ipc::sock::SockPair&& pair);
    ProcessRet setSendBlock(util::time::Time* overtime);
    ProcessRet setRecvBlock(util::time::Time* overtime);
    ProcessRet setNonBlock();

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
