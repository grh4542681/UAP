#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "mempool.h"

namespace ds {

template < typename T >
class HashTable {
public:
    
    HashTable(unsigned long size) : size_(size) {
        freesize_ = size_;
        mp = pub::MemPool::getInstance();
        memblock = mp->Malloc(sizeof(T)*size);
        memset(memblock, 0x00, sizeof(T)*size);
    }

    HashTable(unsigned long size, unsigned long (*hashcode)(T&)) : size_(size), hashcode_(hashcode) {
        freesize_ = size_;
        mp = pub::MemPool::getInstance();
        memblock = mp->Malloc(sizeof(T)*size);
        memset(memblock, 0x00, sizeof(T)*size);
    }

    ~HashTable() {
        clear();
    }

    unsigned long size() { return size_; }
    unsigned long count() { return count_; }

    T* insert(T& data) {
        return insert(std::move(data));
    }
    T* insert(T&& data) {
        unsigned long hash = hashcode_(data);
        if (hash > size_) {
            return NULL;
        }
        void* offset = reinterpret_cast<char*>(memblock) + hash * sizeof(T);
        if (*reinterpret_cast<char*>(offset)) {
            pub::MemPool::Destruct<T>(offset);
        }
        T* pnode = pub::MemPool::Construct<T>(offset, data);
        return pnode;
    }
    template<typename ... Args>
    T* insert(Args&& ... args) {

    }

    void remove(T& data) {

    }
    void remove(T&& data) {

    }

    T* find(T& data) {

    }
    T* find(T&& data) {
        
    }

    void clear() {

    }

private:
    unsigned long size_;
    unsigned long freesize_;
    unsigned long count_;
    unsigned long (*hashcode_)(T&);
    pub::MemPool* mp;
    void* memblock;
};

} //namespace end

#endif
