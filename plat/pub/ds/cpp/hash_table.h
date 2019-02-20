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

typedef unsigned long (*StringHash)(char*, unsigned long);

template < typename T, typename F = StringHash >
class HashTable {
public:
    
    HashTable(unsigned long size) : size_(size) {
        freesize_ = size_;
        count_ = 0;
        thread_safe_flag_ = false;
        mp = pub::MemPool::getInstance();
        memblock = mp->Malloc(sizeof(T)*size);
        memset(memblock, 0x00, sizeof(T)*size);
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

    template<typename ... Args>
    unsigned long gethash(Args&& ... args) {
        return hashcode_(std::forward<Args>(args)...);
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
    T* insert(unsigned long hash, Args&& ... args) {
        if (hash > size_) {
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
        unsigned long hash = hashcode_(std::forward<Args>(args)...);
        if (hash > size_) {
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
        unsigned long hash = hashcode_(std::forward<Args>(args)...);
        if (hash > size_) {
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
        unsigned long hash = hashcode_(std::forward<Args>(args)...);
        if (hash > size_) {
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

private:
    unsigned long size_;
    unsigned long freesize_;
    unsigned long count_;
    bool thread_safe_flag_;
    F hashcode_;
    pub::MemPool* mp;
    thread::ThreadRWLock rwlock_;
    void* memblock;
};

} //namespace end

#endif
