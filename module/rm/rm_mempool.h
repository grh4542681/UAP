#ifndef __RM_MEMPOOL_H__
#define __RM_MEMPOOL_H__

#include <stdlib.h>
#include <utility>
#include <string.h>
#include "rm_controllable.h"

namespace rm {

class RMMemPool{
public:

    void* Malloc(size_t size);
    void Free(void* ptr);

    template < typename T, typename ... Args> T* Malloc(Args&& ... args){
        T* ptr = (T*)malloc(sizeof(T));
        memset((char*)ptr, 0x00, sizeof(T));
        return (new(ptr) T(std::forward<Args>(args)...));
    }
    template < typename T > void Free(T* ptr){
        ptr->~T();
        free(ptr);
    }
    template < typename T, typename ... Args> T* Reset(T* ptr, Args&& ... args){
        ptr->~T();
        memset((char*)ptr, 0x00, sizeof(T));
        return (new(ptr) T(std::forward<Args>(args)...));
    }

    static RMMemPool* getInstance();
private:
    RMMemPool();
    ~RMMemPool();
    thread_local static RMMemPool* pInstance;
};

}//namespace rm end

#endif
