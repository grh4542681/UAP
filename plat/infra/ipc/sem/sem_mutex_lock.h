#ifndef __SEM_MUTEX_LOCK_H__
#define __SEM_MUTEX_LOCK_H__

#include <string>

#include "mempool.h"
#include "sem.h"
#include "sem_sysv.h"
#include "sem_posix.h"

namespace ipc::sem {

class SemMutexLock {
public:
    SemMutexLock();
    SemMutexLock(std::string path);
    ~SemMutexLock();

    template < typename T = SemSysV > IpcRet Create();
    template < typename T = SemSysV > IpcRet Create(mode_t mode);
    IpcRet Destroy();
    template < typename T = SemSysV > IpcRet Open();
    template < typename T = SemSysV > IpcRet Open(IpcMode mode);
    IpcRet Close();

    IpcRet Lock(util::time::Time* overtime);
    IpcRet UnLock();

private:
    Sem* sem_;
    mempool::MemPool* mp_;
    bool init_flag_;
};

}

#endif
