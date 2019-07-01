#ifndef __MSG_SHM_H__
#define __MSG_SHM_H__

#include "msg.h"

namespace ipc::msg {

class MsgShm : public Msg {
public:
    MsgShm();
    MsgShm(std::string path);
    ~MsgShm();

    IpcRet Create()
};

}

#endif
