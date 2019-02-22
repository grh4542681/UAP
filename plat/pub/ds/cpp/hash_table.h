/*******************************************************
# Copyright (C) For free.
# All rights reserved.
# ******************************************************
# Author       : Ronghua Gao
# Last modified: 2019-02-04 07:10
# Email        : grh4542681@163.com
# Filename     : hash_table.h
# Description  : Hash table data struct.
* ******************************************************/
#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "mempool.h"
#include "thread_rw_lock.h"

namespace ds {

enum class HashTableRet : int {
    SUCCESS = 0,
    ERROR = -999,
    EHASHINDEX,
    ERLOCK,
    EWLOCK,
    EUNLOCK,
};

typedef unsigned long (*StringHash)(const char*);

template < typename T, typename F = StringHash >
class HashTable {
public:
    //hash function
    static unsigned long BKDRHash(const char* str) {
        unsigned long hash = 0;
        if (!str) {
            return 0;
        }
        while (*str) {
            hash = hash * 31 + (*str++);
        }
        return (hash);
    }

public:
    
    HashTable(unsigned long size) : size_(size) {
        freesize_ = size_;
        count_ = 0;
        thread_safe_flag_ = false;
        mp = pub::MemPool::getInstance();
        memblock = mp->Malloc(sizeof(T)*size);
        memset(memblock, 0x00, sizeof(T)*size);
        hashcode_ = BKDRHash;
    }

    HashTable(unsigned long size, F hashcode) : size_(size), hashcode_(hashcode) {
        freesize_ = size_;
        count_ = 0;
        thread_safe_flag_ = false;
        mp = pub::MemPool::getInstance();
        memblock = mp->Malloc(sizeof(T)*size);
        memset(memblock, 0x00, sizeof(T)*size);
    }

    ~HashTable() {
        clear();
    }

    unsigned long size() { return size_; }
    unsigned long count() { return count_; }
    unsigned long available() { return freesize_; }
    void setThreadSafe(bool flag) { thread_safe_flag_ = flag; }
    bool getThreadSafe() { return thread_safe_flag_; }
    void setNonBlock(bool flag) { rwlock_.setNonBlock(flag); }
    bool getNonBlock() { return rwlock_.getNonBlock(); }
    HashTableRet getLastRet(){ return last_return_; }

    template<typename ... Args>
    unsigned long hashcode(Args&& ... args) {
        return (hashcode_(std::forward<Args>(args)...) % size_);
    }

    /**
    * @brief insert - Insert an object into a hash table.
    *
    * @tparam [Args] - Parameter package template.
    * @param [hash] - Index in hash table.
    * @param [args] - Parameters for construct object.
    *
    * @returns  Object pointer.
    */
    template<typename ... Args>
    T* insert(Args&& ... args, unsigned long hash) {
        if (hash > size_) {
            _setret(HashTableRet::EHASHINDEX);
            return NULL;
        }
        void* offset = reinterpret_cast<char*>(memblock) + hash * sizeof(T);
        T* pnode = NULL;
        if (*reinterpret_cast<char*>(offset)) {
            pub::MemPool::Destruct<T>(reinterpret_cast<T*>(offset));
            pnode = pub::MemPool::Construct<T>(offset, std::forward<Args>(args)...);
        } else {
            pnode = pub::MemPool::Construct<T>(offset, std::forward<Args>(args)...);
            ++count_;
            --freesize_;
        }
        return pnode;
    }

    /**
    * @brief insert - Insert an object into a hash table.
    *
    * @tparam [Args] - Parameter package template.
    * @param [data] - Object reference.
    * @param [args] - Parameters for hash function.
    *
    * @returns  Object pointer.
    */
    template<typename ... Args>
    T* insert(T& data, Args&& ... args) {
        return insert(std::move(data), std::forward<Args>(args)...);
    }
    template<typename ... Args>
    T* insert(T&& data, Args&& ... args) {
        unsigned long hash = hashcode_(std::forward<Args>(args)...) % size_;
        if (hash > size_) {
            _setret(HashTableRet::EHASHINDEX);
            return NULL;
        }
        void* offset = reinterpret_cast<char*>(memblock) + hash * sizeof(T);
        T* pnode = NULL;
        if (*reinterpret_cast<char*>(offset)) {
            pub::MemPool::Destruct<T>(reinterpret_cast<T*>(offset));
            pnode = pub::MemPool::Construct<T>(offset, data);
        } else {
            pnode = pub::MemPool::Construct<T>(offset, data);
            ++count_;
            --freesize_;
        }
        return pnode;
    }

    /**
    * @brief insert - Insert an object into a hash table.
    *
    * @param [data] - Object referene.
    * @param [hash] - Index in hash table.
    *
    * @returns  Object pointer.
    */
    T* insert(T& data, unsigned long hash) {
        return insert(std::move(data), hash);
    }
    T* insert(T&& data, unsigned long hash) {
        if (hash > size_) {
            _setret(HashTableRet::EHASHINDEX);
            return NULL;
        }
        void* offset = reinterpret_cast<char*>(memblock) + hash * sizeof(T);
        T* pnode = NULL;
        if (*reinterpret_cast<char*>(offset)) {
            pub::MemPool::Destruct<T>(reinterpret_cast<T*>(offset));
            pnode = pub::MemPool::Construct<T>(offset, data);
        } else {
            pnode = pub::MemPool::Construct<T>(offset, data);
            ++count_;
            --freesize_;
        }
        return pnode;
    }

    /**
    * @brief remove - Remove an object from hash table.
    *
    * @tparam [Args] - Parameter package template.
    * @param [args] - Parameters for hash function.
    */
    template<typename ... Args>
    void remove(Args&& ... args) {
        unsigned long hash = hashcode_(std::forward<Args>(args)...) % size_;
        remove(hash);
    }
    void remove(unsigned long hash) {
        if (hash > size_) {
            _setret(HashTableRet::EHASHINDEX);
            return;
        }
        void* offset = reinterpret_cast<char*>(memblock) + hash * sizeof(T);
        if (*reinterpret_cast<char*>(offset)) {
            pub::MemPool::Destruct<T>(reinterpret_cast<T*>(offset));
            memset(offset, 0x00, sizeof(T));
            --count_;
            ++freesize_;
        }
    }

    /**
    * @brief find - Find an object from hash table
    *
    * @tparam [Args] - Parameter package template.
    * @param [args] - Parameters for hash function.
    *
    * @returns  Object pointer.
    */
    template<typename ... Args>
    T* find(Args&& ... args) {
        unsigned long hash = hashcode_(std::forward<Args>(args)...) % size_;
        return find(hash);
    }
    T* find(unsigned long hash) {
        if (hash > size_) {
            _setret(HashTableRet::EHASHINDEX);
            return NULL;
        }
        void* offset = reinterpret_cast<char*>(memblock) + hash * sizeof(T);
        return (*reinterpret_cast<char*>(offset)) ? reinterpret_cast<T*>(offset) : NULL;
    }

    /**
    * @brief clear - Clean hash table
    */
    void clear() {
        for (unsigned long loop = 0; loop < size_; loop++) {
            void* offset = reinterpret_cast<char*>(memblock) + loop * sizeof(T);
            if (*reinterpret_cast<char*>(offset)) {
                pub::MemPool::Destruct<T>(reinterpret_cast<T*>(offset));
                memset(offset, 0x00, sizeof(T));
                --count_;
                ++freesize_;
            }
        }
    }

    HashTableRet rlock(struct timespec* overtime) {
        if (!thread_safe_flag_) {
            return HashTableRet::SUCCESS;
        } else {
            if (rwlock_.RLock(overtime) != thread::ThreadRet::SUCCESS) {
                return HashTableRet::ERLOCK;
            } else {
                return HashTableRet::SUCCESS;
            }
        }
    }
    HashTableRet wlock(struct timespec* overtime) {
        if (!thread_safe_flag_) {
            return HashTableRet::SUCCESS;
        } else {
            if (rwlock_.WLock(overtime) != thread::ThreadRet::SUCCESS) {
                return HashTableRet::EWLOCK;
            } else {
                return HashTableRet::SUCCESS;
            }
        }
    }
    HashTableRet unlock() {
        if (rwlock_.UnLock() != thread::ThreadRet::SUCCESS) {
            return HashTableRet::EUNLOCK;
        } else {
            return HashTableRet::SUCCESS;
        }
    }

private:
    unsigned long size_;
    unsigned long freesize_;
    unsigned long count_;
    bool thread_safe_flag_;
    F hashcode_;
    pub::MemPool* mp;
    thread::ThreadRWLock rwlock_;
    void* memblock;

    HashTableRet last_return_;
    void _setret(HashTableRet ret) { last_return_ = ret; }
};

} //namespace end

#endif
