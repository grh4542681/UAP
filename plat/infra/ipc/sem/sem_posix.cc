#include <stdio.h>
#include <string.h>

#include "ipc_log.h"
#include "sem_posix.h"

namespace ipc::sem {

SemPosix::SemPosix() : Sem()
{
    semset_.clear();
}

SemPosix::SemPosix(std::string path) : Sem(path)
{
    semset_.clear();
}

SemPosix::~SemPosix()
{
    if (init_flag_) {
        Close();
    }
}

IpcRet SemPosix::Create(size_t semnum, mode_t mode)
{
    if (init_flag_) {
        return IpcRet::SUCCESS;
    }

    size_t loop = 0;
    for (loop = 0; loop < semnum; loop++) {
        std::string real_name  = path_ + "_" + std::to_string(loop);
        sem_t* psem = sem_open(real_name.c_str(), O_RDWR|O_CREAT|O_EXCL, mode);
        if (psem == SEM_FAILED) {
            int tmperrno = errno;
            IPC_ERROR("Create posix semaphore set [%s] index[%ld] failed, errno[%s]", path_.c_str(), loop, strerror(tmperrno));
            Destroy();
            return _errno2ret(tmperrno);
        }
        semset_.insert_or_assign(real_name, psem);
    }
    for(auto it : semset_) {
        printf("realname %s\n", it.first.c_str());
    }
    semnum_ = semset_.size();
    init_flag_ = true;
    return IpcRet::SUCCESS;
}

IpcRet SemPosix::Destroy()
{
    if (!semset_.empty()) {
        for(auto it : semset_) {
            if (sem_unlink(it.first.c_str()) < 0) {
                int tmperrno = errno;
                IPC_ERROR("Destroy posix semaphore set [%s] realpath[%s] failed, errno[%s]", path_.c_str(), it.first.c_str(), strerror(tmperrno));
                return _errno2ret(tmperrno);
            }
        }
    }
    init_flag_ = false;
    return IpcRet::SUCCESS;
}

IpcRet SemPosix::Open(IpcMode mode)
{
    return IpcRet::SUCCESS;
}

IpcRet SemPosix::Close()
{
    return IpcRet::SUCCESS;
}

IpcRet SemPosix::_p(size_t sem_index, unsigned int num, util::time::Time* overtime)
{
    return IpcRet::SUCCESS;
}

IpcRet SemPosix::_v(size_t sem_index, unsigned int num)
{
    return IpcRet::SUCCESS;
}

}
