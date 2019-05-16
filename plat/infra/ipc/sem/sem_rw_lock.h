#ifndef __SEM_RW_LOCK_H__
#define __SEM_RW_LOCK_H__

#include <string>

#include "mempool.h"

#include "sem.h"
#include "sem_sysv.h"
#include "sem_posix.h"

namespace ipc::sem {

enum class SemRWLockMode {
    PreferRead,
    PreferWrite,
};

enum class SemRWLockState {
    RLocked,
    WLocked,
    NLocked,
}

template < typename SEMT = SemSysV, typename SHMT = ShmSysV>
class SemRWLock {
public:
    struct SemRWLockInfo {
        bool internal_non_block_flag_;
        unsigned int user_num_;
        SemRWLockMode rwlock_mode_;
        unsigned int reader_num_;
        unsigned int wait_reader_num_;
        unsigned int writer_num_;
        unsigned int wait_writer_num_;
    }

public:
    SemRWLock(std::string path) {
        path_ = path;
        sem_path_ = path_ + "sem";
        shm_path_ = path_ + "shm";
        sem_ = NULL;
        shm_ = NULL;
        rw_info_ = NULL;
        mempool_ = mempool::MemPool::getInstance();
        init_flag_ = false;
        rwlock_state_ = SemRWLockState::NLocked;
    }
    ~SemRWLock() {
        if (init_flag_) {
            Close();
            init_flag_ = false;
        }
        if (sem_) {
            mempool_->Free<SEMT>(sem_);
        }
        if (shm_) {
            mempool_->Free<SHMT>(shm_);
        }
    }

    IpcRet Create(mode_t mode) {
        IpcRet ret = IpcRet::SUCCESS;
        sem_ = mempool_->Malloc<SEMT>(sem_path_);
        if (!sem_) {
            IPC_ERROR("Alloc memory for sem[%s] failed in RWLock", sem_path_.c_str());
            return IpcRet::EMALLOC;
        }
        ret = sem_->Create(3, mode);
        if (ret != IpcRet::SUCCESS) {
            IPC_ERROR("Create sem[%s] failed in RWLock, ret[%d]", sem_path_.c_str(), ret);
            return ret;
        }

        shm_ = mempool_->Malloc<SHMT>(shm_path_);
        if (!shm_) {
            IPC_ERROR("Alloc memory for shm[%s] failed in RWLock", shm_path_.c_str());
            return IpcRet::EMALLOC;
        }
        ret = shm_->Create(sizeof(struct SemRWLockInfo), mode);
        if (ret != IpcRet::SUCCESS) {
            IPC_ERROR("Create shm[%s] failed in RWLock, ret[%d]", shm_path_.c_str(), ret);
            return ret;
        }

        rwlock_info_ = shm_->GetHeadPtr();
        rwlock_info_->non_block_flag_ = false;
        rwlock_info_->user_num_ = 0;
        rwlock_info_->rwlock_mode_ = SemRWLockMode::PerferRead;
        rwlock_info_->reader_num_ = 0;
        rwlock_info_->wait_reader_num_ = 0;
        rwlock_info_->writer_num_ = 0;
        rwlock_info_->wait_writer_num_ = 0;

        return ret;
    }

    IpcRet Destroy() {
        IpcRet ret = IpcRet::SUCCESS;
        if (sem_) {
            ret =sem_->Destroy();
            sem_ = NULL;
        } else {
            SEMT sem(sem_path_);
            ret = sem.Destroy();
        }
        if (ret != IpcRet::SUCCESS) {
            IPC_ERROR("Destroy sem[%s] failed in RWLock, ret[%d]", sem_path_.c_str(), ret_);
            return ret;
        }

        if (shm_) {
            ret = shm_->Destroy();
            shm_ = NULL;
        } else {
            SHMT shm(shm_path_);
            ret = shm.Destroy();
        }
        if (ret != IpcRet::SUCCESS) {
            IPC_ERROR("Destroy shm[%s] failed in RWLock, ret[%d]", shm_path_.c_str(), ret_);
            return ret;
        }
        return ret;
    }

    IpcRet Open() {
        IpcRet ret = IpcRet::SUCCESS;
        if (!sem_) {
            sem_ = mempool_->Malloc<SEMT>(sem_path_);
            if (!sem_) {
                IPC_ERROR("Alloc memory for sem[%s] failed in RWLock", sem_path_.c_str());
                return IpcRet::EMALLOC;
            }
        }
        if (!shm_) {
            shm_ = mempool_->Malloc<SHMT>(shm_path_);
            if (!shm_) {
                IPC_ERROR("Alloc memory for shm[%s] failed in RWLock", shm_path_.c_str());
                return IpcRet::EMALLOC;
            }
        }
        ret = sem_->Open(IpcMode::READ_WRITE);
        if (ret != IpcRet::SUCCESS) {
            return ret;
        }
        ret = shm_->Open(IpcMode::READ_WRITE);
        if (ret != IpcRet::SUCCESS) {
            return ret;
        }
        rwlock_info_ = shm_->GetHeadPtr();
        init_flag_ = true;
        return ret;
    }

    IpcRet Close() {
        IpcRet ret = IpcRet::SUCCESS;
        if (init_flag_) {
            UnLock();
            ret = sem_.Close();
            if (ret != IpcRet::SUCCESS) {
                return ret;
            }
            ret = shm_.Close();
            if (ret != IpcRet::SUCCESS) {
                return ret;
            }
        } else {
            ret = IpcRet::EINIT;
        }
        init_flag_ = false;
        return ret;
    }

    IpcRet SetPerfer(SemRWLockMode mode) {
        IpcRet ret = IpcRet::SUCCESS;
        ret = _ctrl_mutex_lock();
        if (ret == IpcRet::SUCCESS) {
            rwlock_info_->rw_mode_ = mode;
            _ctrl_mutex_unlock();
            return IpcRet::SUCCESS;
        } else {
            return ret;
        }
    }

    IpcRet RLock(util::time::Time* overtime);
    IpcRet WLock(util::time::Time* overtime);
    IpcRet UnLock();
private:
    mempool::MemPool* mempool_;
    bool init_flag_;
    std::string path_;

    std::string shm_path_;
    std::string sem_path_;
    Shm shm_*;
    Sem sem_*;
    struct SemRWLockInfo* rwlock_info_;
    SemRWLockState rwlock_state_;

    IpcRet _ctrl_mutex_lock() {
        return sem_->P(0, NULL);
    }
    IpcRet _ctrl_mutex_unlock() {
        return sem_->V(0, NULL);
    }

    IpcRet _read_mutex_lock() {
        return sem_->P(1, NULL);
    }
    IpcRet _read_mutex_unlock() {
        return sem_->V(1, NULL);
    }

    IpcRet _write_mutex_lock() {
        return sem_->P(2, NULL);
    }
    IpcRet _write_mutex_unlock() {
        return sem_->V(2, NULL);
    }
};

}

#endif
