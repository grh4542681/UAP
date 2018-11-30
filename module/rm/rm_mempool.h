#ifndef __RM_MEMPOOL_H__
#define __RM_MEMPOOL_H__

#include <stdlib.h>
#include "rm_controllable.h"

namespace rm {

class RMMemPool{
public:

    void* Malloc(size_t size);
    void Free(void* ptr);

    template < typename T, typename ... Args> T* Malloc(Args&& ... args);
    template < typename T > void Free(T* ptr);
    template < typename T, typename ... Args> T* Reset(T* ptr, Args&& ... args);

    static RMMemPool* getInstance();
private:
    RMMemPool();
    ~RMMemPool();
    thread_local static RMMemPool* pInstance;
};

}//namespace rm end

#endif
