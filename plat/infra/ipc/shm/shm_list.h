#ifndef __SHM_LIST_H__
#define __SHM_LIST_H__

#include <string>
#include <typeinfo>

#include "time/time_c.h"

#include "shm_sysv.h"
#include "shm_posix.h"

namespace ipc::shm {

template < typename T >
class ShmList {
public:
    typedef struct _ShmListHead {
        std::string object_name_;
        size_t object_size_;
        size_t object_max_num_;
        size_t object_cur_num_;
        T* object_head_;

        bool rw_lock_enable_;
        bool mutex_lock_enable_;

        util::time::Time create_time_;
        util::time::Time last_access_time_;
    } ShmListHead;

    typedef struct _ShmListNode {
        struct _ShmListNode* prev;
        struct _ShmListNode* next;
    } ShmListNode;
public:
    ShmList(std::string path) {
        shm_ = ShmPosix(path);
        p_shm_head_ = NULL;
    }
    ~ShmList() {
        p_shm_head_ = NULL;
    }

    Shm& GetShm() {
        return shm_;
    }

    std::string GetObjectName() {
        std::string name = "";
        if (p_shm_head_) {
            name = p_shm_head_->object_name_;
        }
        return name;
    }

    size_t GetObjectSize() {
        if (p_shm_head_) {
            return p_shm_head_->object_size_;
        }
        return 0;
    }

    size_t GetObjectNumber() {
        if (p_shm_head_) {
            return p_shm_head_->object_max_num_;
        }
        return 0;
    }

    IpcRet Create(size_t obj_num, mode_t mode) {
        size_t shm_size = sizeof(ShmListHead) + obj_num * (sizeof(T) + sizeof(long));
        IpcRet ret = shm_.Create(shm_size, mode);
        if (ret != IpcRet::SUCCESS) {
            return ret;
        }
        ret = shm_.Open(IpcMode::READ_WRITE);
        if (ret == IpcRet::SUCCESS) {
            p_shm_head_ = reinterpret_cast<ShmListHead*>(shm_.GetHeadPtr());

            p_shm_head_->object_name_.assign(typeid(T).name());
            p_shm_head_->object_size_ = sizeof(T);
            p_shm_head_->object_max_num_ = obj_num;
            p_shm_head_->object_cur_num_ = 0;
            p_shm_head_->object_head_ = NULL;

            p_shm_head_->create_time_ = util::time::NowC();
        }
        ret = shm_.Close();
        if (ret == IpcRet::SUCCESS) {
            p_shm_head_ = NULL;
        }

        return ret;
    }
    IpcRet Destroy() {
        IpcRet ret = shm_.Destroy();
        if (ret == IpcRet::SUCCESS) {
            p_shm_head_ = NULL;
        }
        return ret;
    }
    IpcRet Open(IpcMode mode) {
        IpcRet ret = shm_.Open(mode);
        if (ret == IpcRet::SUCCESS) {
            p_shm_head_ = reinterpret_cast<ShmListHead*>(shm_.GetHeadPtr());

            p_shm_head_->last_access_time_ = util::time::NowC();
        }
        return ret;
    }
    IpcRet Close() {
        IpcRet ret = shm_.Close();
        if (ret == IpcRet::SUCCESS) {
            p_shm_head_ = NULL;
        }
        return ret;
    }

    IpcRet Pusb(T&& data) {
        return IpcRet::SUCCESS;
    }

    IpcRet Pop() {
        return IpcRet::SUCCESS;
    }

    IpcRet Format();

private:
    ShmListHead* p_shm_head_;
    ShmPosix shm_;
};

}

#endif
