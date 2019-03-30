#ifndef __PROCESS_RW_LOCK_POSIX_H__
#define __PROCESS_RW_LOCK_POSIX_H__

#include "process_return.h"
#include "process_log.h"

namespace process::mutex {

class PosixRWLock : public RWLock{
public:
    PosixRWLock();
    ~PosixRWLock();

    ProcessRet RLock();
    ProcessRet RUnLock();
    ProcessRet WLock();
    ProcessRet WUnLock();
private:
    
};

}

#endif
