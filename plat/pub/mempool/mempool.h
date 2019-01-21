#ifndef __MEMPOOL_MEMPOOL_H__
#define __MEMPOOL_MEMPOOL_H__

#include <stdlib.h>
#include <utility>
#include <string.h>

namespace pub {

class MempoolCenter{
public:
    static MempoolCenter* getInstance();
private:
    MempoolCenter();
    ~MempoolCenter();
    static MempoolCenter* pInstance;
};

class MemPool{
public:

    void* Malloc(size_t size);
    void Free(void* ptr);

    template < typename T > T* Malloc(T&& other){
        T* ptr = (T*)malloc(sizeof(T));
        memset((char*)ptr, 0x00, sizeof(T));
        memcpy(ptr, &other, sizeof(T));
        return ptr;
    }
    template < typename T, typename ... Args> T* Malloc(Args&& ... args){
        T* ptr = (T*)malloc(sizeof(T));
        memset((char*)ptr, 0x00, sizeof(T));
        return (new(ptr) T(std::forward<Args>(args)...));
    }

    template < typename T > T* Reset(T* ptr, T&& other){
        ptr->~T();
        memset((char*)ptr, 0x00, sizeof(T));
        memcpy(ptr, &other, sizeof(T));
        return ptr;
    }
    template < typename T, typename ... Args> T* Reset(T* ptr, Args&& ... args){
        ptr->~T();
        memset((char*)ptr, 0x00, sizeof(T));
        return (new(ptr) T(std::forward<Args>(args)...));
    }

    template < typename T > void Free(T* ptr){
        ptr->~T();
        free(ptr);
    }

    static MemPool* getInstance();
private:
    MemPool();
    ~MemPool();
    thread_local static MemPool* pInstance;
};


}//namespace pub end

#endif
