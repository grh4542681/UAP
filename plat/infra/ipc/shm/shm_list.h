/*******************************************************
 * Copyright (C) For free.
 * All rights reserved.
 *******************************************************
 * @author   : Ronghua Gao
 * @date     : 2019-07-01 10:35
 * @file     : shm_list.h
 * @brief    : A list on share memory.
 * @note     : Email - grh4542681@163.com
 * ******************************************************/
#ifndef __SHM_LIST_H__
#define __SHM_LIST_H__

#include <string>
#include <typeinfo>
#include <type_traits>
#include <iterator>

#include "time_c.h"
#include "bitmap/bitmap.h"

#include "shm_sysv.h"
#include "shm_posix.h"

namespace ipc::shm {

/**
* @brief - A share memory list.
*
* @tparam [T] - Element type.
*/
template < typename T >
class ShmList {
public:
    typedef struct _ShmListNode {
        size_t index;
        struct _ShmListNode* prev;
        struct _ShmListNode* next;
    } ShmListNode;

    typedef struct _ShmListHead {
        std::string object_name_;
        size_t object_size_;
        size_t object_max_num_;
        size_t object_cur_num_;
        void* object_bitmap_;
        void* object_data_area_;

        ShmListNode* object_head_;
        ShmListNode* object_tail_;

        bool rw_lock_enable_;
        bool mutex_lock_enable_;

        timer::Time create_time_;
        timer::Time last_access_time_;
    } ShmListHead;

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

    size_t GetObjectMaxNumber() {
        if (p_shm_head_) {
            return p_shm_head_->object_max_num_;
        }
        return 0;
    }

    size_t GetObjectCurNumber() {
        if (p_shm_head_) {
            return p_shm_head_->object_cur_num_;
        }
        return 0;
    }

    IpcRet Create(size_t obj_num, mode_t mode) {
        size_t shm_size = sizeof(ShmListHead) + ((obj_num + 8 - 1) / 8)  + obj_num * (sizeof(T) + sizeof(ShmListNode));
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
            p_shm_head_->object_bitmap_ = reinterpret_cast<void*>(reinterpret_cast<char*>(shm_.GetHeadPtr()) + sizeof(ShmListHead));
            p_shm_head_->object_data_area_ = reinterpret_cast<char*>(shm_.GetHeadPtr()) + sizeof(ShmListHead) + (((obj_num + 64 - 1) / 64) * sizeof(long));
            p_shm_head_->object_head_ = NULL;
            p_shm_head_->object_tail_ = NULL;

            p_shm_head_->create_time_ = timer::NowC();
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

            p_shm_head_->last_access_time_ = timer::NowC();
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

    template < typename ... Args > T* PushBefore(iterator& node, Args&& ... args) {
        return _push_before(node.ptr, std::forward<Args>(args)...);
    }
    template < typename ... Args > T* PushAfter(iterator& node, Args&& ... args) {
        return _push_after(node.ptr, std::forward<Args>(args)...);
    }
    template < typename ... Args > T* PushHead(Args&& ... args) {
        return _push_before(p_shm_head_->object_head_, std::forward<Args>(args)...);
    }
    template < typename ... Args > T* PushTail(Args&& ... args) {
        return _push_after(p_shm_head_->object_tail_, std::forward<Args>(args)...);
    }

    void Pop(iterator& node) {
        _pop(node.ptr);
    }
    void PopHead() {
        _pop(p_shm_head_->object_head_);
    }
    void PopTail() {
        _pop(p_shm_head_->object_tail_);
    }

    IpcRet Format();

private:
    template < typename ... Args > T* _push_before(ShmListNode* node, Args&& ... args) {
        void* parea = NULL;
        T* pdata = NULL;
        ShmListNode* pnode = NULL;
        size_t bit_index = 0;

        if (!p_shm_head_) {
            ret_ = IpcRet::EINIT;
            return NULL;
        }
        if (p_shm_head_->object_max_num_ == p_shm_head_->object_cur_num_) {
            ret_ = IpcRet::SL_ENOSPACE;
            return NULL;
        }

        util::bitmap::Bitmap bm(p_shm_head_->object_max_num_, p_shm_head_->object_bitmap_);
        bit_index = bm.Find0();
        if (bit_index == 0) {
            ret_ = IpcRet::SL_EBITMAP;
            return NULL;
        }
        parea = reinterpret_cast<void*>(reinterpret_cast<char*>(p_shm_head_->object_data_area_) + ((bit_index -1 ) * (sizeof(T) + sizeof(ShmListNode))));
        pdata  = mempool::MemPool::Construct<T>(parea, std::forward<Args>(args)...);
        if (!pdata) {
            ret_ = IpcRet::ECONSTRUCT;
            return NULL;
        }

        if (bm.Set(bit_index) != util::bitmap::BitmapRet::SUCCESS) {
            ret_ = IpcRet::SL_EBITMAP;
            return NULL;
        }

        pnode = reinterpret_cast<ShmListNode*>(reinterpret_cast<char*>(parea) + sizeof(T));
        pnode->index = bit_index;

        if (!node) {
            if (!p_shm_head_->object_head_ && !p_shm_head_->object_tail_) {
                p_shm_head_->object_head_ = p_shm_head_->object_tail_ = pnode;
                pnode->next = pnode->prev = NULL;
            } else {
                p_shm_head_->object_head_->prev = pnode;
                pnode->next = p_shm_head_->object_head_;
                pnode->prev = NULL;
                p_shm_head_->object_head_ = pnode;
            }
        } else {
            pnode->next = node;
            pnode->prev = node->prev;
            node->prev = pnode;
            if (node == p_shm_head_->object_head_) {
                p_shm_head_->object_head_ = pnode;
            }
        }

        p_shm_head_->object_cur_num_++;

        return pdata;
    }
    template < typename ... Args > T* _push_after(ShmListNode* node, Args&& ... args) {
        void* parea = NULL;
        T* pdata = NULL;
        ShmListNode* pnode = NULL;
        size_t bit_index = 0;

        if (!p_shm_head_) {
            ret_ = IpcRet::EINIT;
            return NULL;
        }
        if (p_shm_head_->object_max_num_ == p_shm_head_->object_cur_num_) {
            ret_ = IpcRet::SL_ENOSPACE;
            return NULL;
        }

        util::bitmap::Bitmap bm(p_shm_head_->object_max_num_, p_shm_head_->object_bitmap_);
        bit_index = bm.Find0();
        if (bit_index == 0) {
            ret_ = IpcRet::SL_EBITMAP;
            return NULL;
        }
        parea = reinterpret_cast<void*>(reinterpret_cast<char*>(p_shm_head_->object_data_area_) + ((bit_index -1 ) * (sizeof(T) + sizeof(ShmListNode))));
        pdata  = mempool::MemPool::Construct<T>(parea, std::forward<Args>(args)...);
        if (!pdata) {
            ret_ = IpcRet::ECONSTRUCT;
            return NULL;
        }

        if (bm.Set(bit_index) != util::bitmap::BitmapRet::SUCCESS) {
            ret_ = IpcRet::SL_EBITMAP;
            return NULL;
        }

        pnode = reinterpret_cast<ShmListNode*>(reinterpret_cast<char*>(parea) + sizeof(T));
        pnode->index = bit_index;

        if (!node) {
            if (!p_shm_head_->object_head_ && !p_shm_head_->object_tail_) {
                p_shm_head_->object_head_ = p_shm_head_->object_tail_ = pnode;
                pnode->next = pnode->prev = NULL;
            } else {
                p_shm_head_->object_tail_->next = pnode;
                pnode->prev = p_shm_head_->object_tail_;
                pnode->next = NULL;
                p_shm_head_->object_tail_ = pnode;
            }
        } else {
            pnode->prev = node;
            pnode->next = node->next;
            node->next = pnode;
            if (node == p_shm_head_->object_tail_) {
                p_shm_head_->object_tail_ = pnode;
            }
        }

        p_shm_head_->object_cur_num_++;

        return pdata;
    }

    void _pop(ShmListNode* node) {
        if (!p_shm_head_) {
            ret_ = IpcRet::EINIT;
            return;
        }
        if (!node) {
            ret_ = IpcRet::EBADARGS;
            return;
        }

        size_t bit_index = node->index;
        util::bitmap::Bitmap bm(p_shm_head_->object_max_num_, p_shm_head_->object_bitmap_);
        bm.Unset(bit_index);

        T* pdata = reinterpret_cast<T*>(reinterpret_cast<char*>(node) - sizeof(T));
        if (node->next && node->prev) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        } else if (node->next) {
            node->next->prev = node->prev;
            p_shm_head_->object_head_ = node->next;
        } else if (node->prev) {
            node->prev->next = node->next;
            p_shm_head_->object_tail_ = node->prev;
        } else {
            p_shm_head_->object_head_ = p_shm_head_->object_tail_ = NULL;
        }
        mempool::MemPool::Destruct<T>(pdata);

        p_shm_head_->object_cur_num_--;
    }


private:
    ShmListHead* p_shm_head_;
    ShmPosix shm_;
    IpcRet ret_;
};

}

#endif
