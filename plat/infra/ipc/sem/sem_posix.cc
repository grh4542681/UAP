#include <stdio.h>
#include <string.h>

#include "time/time_c.h"

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
    if (path_.empty() || semnum <= 0 ) {
        return IpcRet::EINIT;
    }

    if (init_flag_) {
        return IpcRet::SUCCESS;
    }

    size_t loop = 0;
    for (loop = 0; loop < semnum; loop++) {
        std::string real_name  = path_ + "_" + std::to_string(loop);
        sem_t* psem = sem_open(real_name.c_str(), O_RDWR|O_CREAT|O_EXCL, mode, 0);
        if (psem == SEM_FAILED) {
            int tmperrno = errno;
            IPC_ERROR("Create posix semaphore set [%s] index[%ld] failed, errno[%s]", path_.c_str(), loop, strerror(tmperrno));
            return _errno2ret(tmperrno);
        }
        semset_.insert_or_assign(real_name, psem);
    }
    semnum_ = semset_.size();
    init_flag_ = true;
    return IpcRet::SUCCESS;
}

IpcRet SemPosix::Destroy()
{
    if (!semset_.empty()) {
        Close();
        for(auto it : semset_) {
            if (sem_unlink(it.first.c_str()) < 0) {
                int tmperrno = errno;
                IPC_ERROR("Destroy posix semaphore set [%s] realpath[%s] failed, errno[%s]", path_.c_str(), it.first.c_str(), strerror(tmperrno));
                return _errno2ret(tmperrno);
            }
        }
    } else {
        int semnum = 0;
        while (1) {
            std::string real_name = path_ + "_" + std::to_string(semnum);
            if (sem_unlink(real_name.c_str()) < 0) {
                int tmperrno = errno;
                if (tmperrno == ENOENT) {
                    break;
                } else {
                    IPC_ERROR("Destroy posix semaphore set [%s] realpath[%s] failed, errno[%s]", path_.c_str(), real_name.c_str(), strerror(tmperrno));
                    return _errno2ret(tmperrno);
                }
            }
            semnum++;
        }
    }
    init_flag_ = false;
    return IpcRet::SUCCESS;
}

IpcRet SemPosix::Open(IpcMode mode)
{
    if (path_.empty()) {
        return IpcRet::EINIT;
    }

    if (init_flag_) {
        return IpcRet::SUCCESS;
    }

    int flags = 0;
    if (mode | IpcMode::READ_ONLY) {
        flags |= O_RDONLY;
    } else if (mode | IpcMode::WRITE_ONLY) {
        flags |= O_WRONLY;   
    } else if (mode | IpcMode::READ_WRITE) {
        flags |= O_RDWR;
    } else {
        return IpcRet::SEM_EMODE;
    }

    semnum_ = 0;
    while(1) {
        std::string real_name = path_ + "_" + std::to_string(semnum_);
        sem_t* psem = sem_open(real_name.c_str(), flags, 0);
        if (psem == SEM_FAILED) {
            int tmperrno = errno;
            if (semnum_ == 0) {
                return _errno2ret(tmperrno);
            } else {
                break;
            }
        }
        semset_.insert_or_assign(real_name, psem);
        semnum_++;
    }
    init_flag_ = true;
    return IpcRet::SUCCESS;
}

IpcRet SemPosix::Close()
{
    if (!init_flag_) {
        return IpcRet::EINIT;
    }

    for(auto it : semset_) {
        sem_close(it.second);
    }

    return IpcRet::SUCCESS;
}

IpcRet SemPosix::_p(size_t sem_index, util::time::Time* overtime)
{
    if (!init_flag_) {
        return IpcRet::EINIT;
    }
    if (sem_index >= semnum_ ) {
        return IpcRet::EBADARGS;
    }

    int tmperrno = 0;

    std::string real_name = path_ + "_" + std::to_string(sem_index);
    auto it = semset_.find(real_name);
    if (it == semset_.end()) {
        IPC_ERROR("Index [%ld] in semaphore set [%s] not found", sem_index, path_.c_str());
        return IpcRet::SEM_ENOTFOUND;
    }
    if (nonblock_flag_) {
        if (sem_trywait(it->second) < 0) {
            tmperrno = errno;
            IPC_ERROR("Semaphore set [%s] index [%ld] P operator failed, errno[%s]", path_.c_str(), sem_index, strerror(tmperrno));
            return _errno2ret(tmperrno);
        }
    } else {
        if (!overtime) {
            if (sem_wait(it->second) < 0) {
                tmperrno = errno;
                IPC_ERROR("Semaphore set [%s] index [%ld] P operator failed, errno[%s]", path_.c_str(), sem_index, strerror(tmperrno));
                return _errno2ret(tmperrno);
            }
        } else {
            if (!overtime->IsPositive()) {
                IPC_ERROR("Overtime is not correct.");
                return IpcRet::EBADARGS;
            }   

            util::time::Time curr_time = util::time::NowC();
            util::time::Time T_intervals = curr_time + *overtime;

            struct timespec intervals;
            memset(&intervals, 0, sizeof(struct timespec));
            T_intervals.To<struct timespec>(&intervals);

            while (curr_time < T_intervals) {
                if (sem_timedwait(it->second, &intervals) < 0) {
                    tmperrno = errno;
                    if (tmperrno == ETIMEDOUT) {
                        return IpcRet::ETIMEOUT;
                    } else if (tmperrno == EINTR) {
                        curr_time = util::time::NowC();
                    } else {
                        IPC_ERROR("Semaphore set [%s] index [%ld] P operator failed, errno[%s]", path_.c_str(), sem_index, strerror(tmperrno));
                        return _errno2ret(tmperrno);
                    }
                } else {
                    return IpcRet::SUCCESS;
                }
            }
        }
    }

    return IpcRet::SUCCESS;
}

IpcRet SemPosix::_v(size_t sem_index)
{
    if (!init_flag_) {
        return IpcRet::EINIT;
    }
    if (sem_index >= semnum_ ) {
        return IpcRet::EBADARGS;
    }

    int tmperrno = 0;

    std::string real_name = path_ + "_" + std::to_string(sem_index);
    auto it = semset_.find(real_name);
    if (it == semset_.end()) {
        IPC_ERROR("Index [%ld] in semaphore set [%s] not found", sem_index, path_.c_str());
        return IpcRet::SEM_ENOTFOUND;
    }

    if (sem_post(it->second) < 0) {
        tmperrno = errno;
        IPC_ERROR("Semaphore set [%s] index [%ld] P operator failed, errno[%s]", path_.c_str(), sem_index, strerror(tmperrno));
        return _errno2ret(tmperrno);
    }
    return IpcRet::SUCCESS;
}

}
