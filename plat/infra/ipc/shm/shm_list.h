#ifndef __SHM_LIST_H__
#define __SHM_LIST_H__

#include <string>
#include <typeinfo>
#include <type_traits>
#include <iterator>

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

    class iterator : public std::iterator<std::input_iterator_tag, ShmListNode> {
    public:
        friend class ShmList;
        iterator(ShmListNode* node = NULL) : ptr(node) { }

        iterator(const iterator& other) : ptr(other.ptr) { } 
        ~iterator() { }
                                                                                                                                                                                            

        T& operator*() { return *(reinterpret_cast<T*>(reinterpret_cast<char*>(ptr) - sizeof(T))); }
        bool operator!=(const iterator& other) const { return (ptr != other.ptr); }
        bool operator==(const iterator& other) const { return (ptr == other.ptr); }
        const iterator& operator--() {
            ptr = ptr->prev;
            return *this;
        }   
        const iterator operator--(int) {
            iterator tmp = *this;
            ptr = ptr->prev;
            return tmp;
        }   
        const iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }   
        const iterator operator++(int) {
            iterator tmp = *this;
            ptr = ptr->next;
            return tmp;
        }
    private:
        ShmListNode* ptr;
    };
public:
    ShmList(std::string path) {
        shm_ = ShmPosix(path);
        p_shm_head_ = NULL;
    }
    ~ShmList() {
        p_shm_head_ = NULL;
    }

    iterator begin () const { return p_shm_head_ ? iterator(p_shm_head_->object_head_) : iterator(NULL); }
    iterator end () const { return iterator(NULL); }

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

    template < typename ... Args > IpcRet Push(Args&& ... args) {
        return IpcRet::SUCCESS;
    }

    IpcRet Pop() {
        return IpcRet::SUCCESS;
    }

    IpcRet Format();

private:
    template < typename ... Args > IpcRet _push_before(ShmListNode* node, Args&& ... args) {
        return IpcRet::SUCCESS;
    }
    template < typename ... Args > IpcRet _push_after(ShmListNode* node, Args&& ... args) {
        return IpcRet::SUCCESS;
    }

    IpcRet pop(ShmListNode* node) {
        return IpcRet::SUCCESS;
    }


private:
    ShmListHead* p_shm_head_;
    ShmPosix shm_;
};

}

#endif
