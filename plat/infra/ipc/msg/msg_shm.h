#ifndef __MSG_SHM_H__
#define __MSG_SHM_H__

#include "shm/shm_posix.h"
#include "sem/sem_posix.h"

#include "msg.h"
#include "ipc_log.h"

namespace ipc::msg {

class MsgShm : public Msg {
public:
    typedef struct _MsgShmHead {
        size_t msg_num;
        size_t free_size;
        void* data_start;
        void* data_end;
        void* msg_head;
        void* msg_tail;
    } MsgShmHead;
public:
    MsgShm();
    MsgShm(std::string path);
    ~MsgShm();

    IpcRet Create(size_t size, mode_t mode);
    IpcRet Destroy();
    IpcRet Open(IpcMode mode);
    IpcRet Close();

    size_t GetMsgNum();
    size_t GetFreeSize();

    size_t Recv(MsgID* id, MsgLevel* level, void* data, size_t data_len, util::time::Time* overtime);
    size_t Send(MsgID* id, MsgLevel* level, void* data, size_t data_len, util::time::Time* overtime);
private:
    shm::ShmPosix shm_;
    sem::SemPosix sem_;

    MsgShmHead* p_shm_head_ = {NULL};
};

}

#endif
