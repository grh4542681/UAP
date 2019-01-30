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
    template<typename ... NArgs, template <typename...> class C, typename ... Args>
    T* insert(const C <NArgs...> &, Args&& ... args) {

    }

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

    template<typename ... Args>
    T* find(Args&& ... args) {
        unsigned long hash = hashcode_(std::forward<Args>(args)...);
        if (hash > size_) {
            return NULL;
        }
        void* offset = reinterpret_cast<char*>(memblock) + hash * sizeof(T);
        return (*reinterpret_cast<char*>(offset)) ? reinterpret_cast<T*>(offset) : NULL;
    }

    void clear() {

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
