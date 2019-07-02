#include "msg_shm.h"

namespace ipc::msg {

MsgShm::MsgShm()
{

}

MsgShm::MsgShm(std::string path) : Msg(path)
{
    if (!path.empty()) {
        shm_ = shm::ShmPosix(path + ".shm");
        sem_ = sem::SemPosix(path + ".sem");
        init_flag_ = true;
    } else {
        init_flag_ = false;
    }
}

MsgShm::~MsgShm()
{

}

size_t MsgShm::GetMsgNum()
{
    if (p_shm_head_) {
        return p_shm_head_->msg_num;
    }
    return 0;
}

size_t MsgShm::GetFreeSize()
{
    if (p_shm_head_) {
        return p_shm_head_->free_size;
    }
    return 0;
}

IpcRet MsgShm::Create(size_t size, mode_t mode)
{
    IpcRet ret = IpcRet::SUCCESS;
    ret = shm_.Create(size, mode);
    if (ret != IpcRet::SUCCESS) {
        return ret;
    }

    ret = sem_.Create(2, mode);
    if (ret != IpcRet::SUCCESS) {
        shm_.Destroy();
        return ret;
    }

    ret = shm_.Open(IpcMode::READ_WRITE);
    if (ret == IpcRet::SUCCESS) {
        p_shm_head_ = reinterpret_cast<MsgShmHead*>(shm_.GetHeadPtr());
        p_shm_head_->msg_num = 0;
        p_shm_head_->free_size = shm_.GetSize() - sizeof(MsgShmHead);
        p_shm_head_->data_start = reinterpret_cast<void*>(reinterpret_cast<char*>(shm_.GetHeadPtr()) + sizeof(MsgShmHead));
        p_shm_head_->data_end = reinterpret_cast<void*>(reinterpret_cast<char*>(shm_.GetHeadPtr()) + shm_.GetSize());
        p_shm_head_->msg_head = p_shm_head_->data_start;
        p_shm_head_->msg_tail = p_shm_head_->data_start;
    } else {
        shm_.Destroy();
        sem_.Destroy();
        return ret;
    }
    shm_.Close();

    return ret;
}

IpcRet MsgShm::Destroy()
{
    shm_.Destroy();
    sem_.Destroy();
    p_shm_head_ = NULL;
    return IpcRet::SUCCESS;
}

IpcRet MsgShm::Open(IpcMode mode)
{
    IpcRet ret = IpcRet::SUCCESS;
    ret = shm_.Open(mode);
    if (ret != IpcRet::SUCCESS) {
        return ret;
    }

    ret = sem_.Open(mode);
    if (ret != IpcRet::SUCCESS) {
        shm_.Close();
        return ret;
    }

    p_shm_head_ = reinterpret_cast<MsgShmHead*>(shm_.GetHeadPtr());

    return ret;
}

IpcRet MsgShm::Close()
{
    shm_.Close();
    sem_.Close();
    p_shm_head_ = NULL;
    return IpcRet::SUCCESS;
}

size_t MsgShm::Recv(MsgID* id, MsgLevel* level, void* data, size_t data_len, util::time::Time* overtime)
{
    return 0;
}

size_t MsgShm::Send(MsgID* id, MsgLevel* level, void* data, size_t data_len, util::time::Time* overtime)
{
    return 0;
}

}
