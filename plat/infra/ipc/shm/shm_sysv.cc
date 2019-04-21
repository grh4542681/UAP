#include <string.h>

#include "ipc_log.h"
#include "shm_sysv.h"

namespace ipc::shm {

ShmSysV::ShmSysV(std::string path) : Shm(path)
{
    key_ = ftok(path.c_str(), 100);
    shmid_ = -1;
}

ShmSysV::ShmSysV() : Shm()
{
    key_ = 0;
    shmid_ = -1;
}

ShmSysV::ShmSysV(const ShmSysV& other) : Shm(other)
{
    key_ = other.key_;
    shmid_ = other.shmid_;
}

ShmSysV::~ShmSysV()
{
    if (shmid_ > 0) {
        Close();
    }
}

IpcRet ShmSysV::Create(mode_t mode, size_t size)
{
    if (shmid_ > 0) {
        return IpcRet::SUCCESS;
    }
    if (path_.empty() || size_ <= 0) {
        return IpcRet::EINIT;
    }
    shmid_ = shmget(key_, size, mode|IPC_CREAT|IPC_EXCL);
    if (shmid_ < 0) {
        int tmp_errno = errno;
        IPC_ERROR("Create sysv share memory error [%s]", strerror(tmp_errno));
        return _errno2ret(tmp_errno);
    }
    struct shmid_ds shm_info;
    memset(&shm_info, 0, sizeof(struct shmid_ds));
    if (shmctl(shmid_, IPC_INFO, &shm_info) < 0) {
        int tmp_errno = errno;
        return _errno2ret(tmp_errno);
    }
    size_ = shm_info.shm_segsz;
    return IpcRet::SUCCESS;
}

IpcRet ShmSysV::Destroy()
{
    if (shmid_ < 0) {
        shmid_ = shmget(key_, 0, 0);
        if (shmid_ < 0) {
            int tmp_errno = errno;
            return _errno2ret(tmp_errno);
        }
    }
    if (shmctl(shmid_, IPC_RMID, NULL) < 0) {
        int tmp_errno = errno;
        return _errno2ret(tmp_errno);
    }
    return IpcRet::SUCCESS;
}

IpcRet ShmSysV::Open(ShmMode mode)
{
    if (path_.empty()) {
        return IpcRet::EINIT;
    }
    if (shmid_ < 0) {
        shmid_ = shmget(key_, 0, 0);
        if (shmid_ < 0) {
            int tmp_errno = errno;
            return _errno2ret(tmp_errno);
        }
    }
    struct shmid_ds shm_info;
    memset(&shm_info, 0, sizeof(struct shmid_ds));
    if (shmctl(shmid_, IPC_INFO, &shm_info) < 0) {
        int tmp_errno = errno;
        return _errno2ret(tmp_errno);
    }
    size_ = shm_info.shm_segsz;
    if (mode | ShmMode::READ_ONLY) {
        head_ = shmat(shmid_, NULL, SHM_RDONLY);
        if ((long)head_ < 0) {
            int tmp_errno = errno;
            head_ = NULL;
            return _errno2ret(tmp_errno);
        }
    } else if ((mode | ShmMode::WRITE_ONLY) || (mode | ShmMode::READ_WRITE)) {
        head_ = shmat(shmid_, NULL, 0);
        if ((long)head_ < 0) {
            int tmp_errno = errno;
            head_ = NULL;
            return _errno2ret(tmp_errno);
        }
    } else {
        return IpcRet::SHM_EMODE;
    }
    return IpcRet::SUCCESS;
}

IpcRet ShmSysV::Close()
{
    if (shmid_ < 0 || head_ == NULL) {
        return IpcRet::EINIT;
    }
    if (shmdt(head_) < 0) {
        int tmp_errno = errno;
        return _errno2ret(tmp_errno);
    }
    head_ = NULL;
    return IpcRet::SUCCESS;
}

IpcRet ShmSysV::Sync()
{
    return IpcRet::SUCCESS;
}

} //namespace end
