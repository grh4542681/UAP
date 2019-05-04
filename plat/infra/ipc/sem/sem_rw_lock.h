#ifndef __SEM_RW_LOCK_H__
#define __SEM_RW_LOCK_H__

#include <string>

#include "mempool.h"

#include "sem.h"
#include "sem_sysv.h"
#include "sem_posix.h"

namespace ipc::sem {

template < typename T = SemSysV >
class SemRWLock {
public:
    SemRWLock();
    SemRWLock(std::string path);
    ~SemRWLock();

private:
    std::string path_;
    Sem* sem_;
    mempool::MemPool* mp_;
    bool init_flag_;
};

}

#endif