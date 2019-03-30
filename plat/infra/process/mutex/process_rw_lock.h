#ifndef __PROCESS_RW_LOCK_H__
#define __PROCESS_RW_LOCK_H__

#include "process_return.h"

namespace process::mutex {

class ProcessRWLock{
public:
    ProcessRWLock(){}
    virtual ~ProcessRWLock();
    virtual ProcessRet RLock();
    virtual ProcessRet RUnLock();
    virtual ProcessRet WLock();
    virtual ProcessRet WUnLock();
};

}

#endif
