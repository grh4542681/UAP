#ifndef __MEMPOOL_MEMPOOL_H__
#define __MEMPOOL_MEMPOOL_H__

#include <stdlib.h>
#include <utility>
#include <string.h>
#include <new>

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
        T* ptr = (T*)Malloc(sizeof(T));
        memset((char*)ptr, 0x00, sizeof(T));
        return (new(ptr) T(std::forward<T>(other));
    }

    template < typename T, typename ... Args> T* Malloc(Args&& ... args){
        T* ptr = (T*)Malloc(sizeof(T));
        memset((char*)ptr, 0x00, sizeof(T));
        return (new(ptr) T(std::forward<Args>(args)...));
    }

    template < typename T > T* Reset(T* ptr, T&& other){
        ptr->~T();
        memset((char*)ptr, 0x00, sizeof(T));
        return (new(ptr) T(std::forward<T>(other));
    }

    template < typename T, typename ... Args> T* Reset(T* ptr, Args&& ... args){
        ptr->~T();
        memset((char*)ptr, 0x00, sizeof(T));
        return (new(ptr) T(std::forward<Args>(args)...));
    }

    template < typename T > void Free(T* ptr){
        ptr->~T();
        Free(ptr);
    }

    static MemPool* getInstance();

    template < typename T, typename ... Args> static T* Construct(void* ptr, T&& other){
        memset((char*)ptr, 0x00, sizeof(T));
        return (new(ptr) T(std::forward<T>(other));
    }

    template < typename T, typename ... Args> static T* Construct(void* ptr, Args&& ... args){
        memset((char*)ptr, 0x00, sizeof(T));
        return (new(ptr) T(std::forward<Args>(args)...));
    }

    template < typename T > static void* Destruct(T* ptr){
        ptr->~T();
        return ptr;
    }
private:
    MemPool();
    ~MemPool();
    thread_local static MemPool* pInstance;
};


}//namespace pub end

#endif
