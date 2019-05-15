#ifndef __SEM_RW_LOCK_H__
#define __SEM_RW_LOCK_H__

#include <string>

#include "mempool.h"

#include "sem.h"
#include "sem_sysv.h"
#include "sem_posix.h"

namespace ipc::sem {

enum class SemRWLockMode {
    PreferRead,
    PreferWrite,
};

template < typename T = SemSysV >
class SemRWLock {
public:
    SemRWLock();
    SemRWLock(std::string path);
    ~SemRWLock();

    IpcRet Create();
    IpcRet Destroy();

    IpcRet SetPerfer(SemRWLockMode mode);

    IpcRet RLock(util::time::Time* overtime);
    IpcRet RUnLock();
    IpcRet WLock(util::time::Time* overtime);
    IpcRet WUnLock();
private:
    std::string path_;
    bool create_flag_;

    SemRWLockMode mode_;
    unsigned int reader_num_;
    unsigned int wait_reader_num_;
    unsigned int writer_num_;
    unsigned int wait_writer_num_;
};

}

#endif
