#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>

#include "mempool.h"

#include "ipc_return.h"
#include "ipc_log.h"
#include "sem_sysv.h"


namespace ipc::sem {

SemSysV::SemSysV() : Sem()
{
    key_ = 0;
    semid_ = -1;
}

SemSysV::SemSysV(std::string path) : Sem(path)
{
    key_ = ftok(path.c_str(), 100);
    semid_ = -1;
}

/**
* @brief ~SemSysV - This function is destructor.
*/
SemSysV::~SemSysV(){
    if (init_flag_) {
        Close();
    }
}

IpcRet SemSysV::Create(size_t semnum, mode_t mode)
{
    int tmp_errno;
    union semun args;

    semid_ = semget(key_, semnum, mode|IPC_CREAT|IPC_EXCL);
    if (semid_ < 0) {
        tmp_errno = errno;
        IPC_ERROR("%s", strerror(tmp_errno));
        return _errno2ret(tmp_errno);
    }

    semnum_ = semnum;

    unsigned short* sem_val = (unsigned short*)(mempool::MemPool::getInstance()->Malloc(semnum * (sizeof(unsigned short))));
    memset(sem_val, 0, semnum* (sizeof(unsigned short)));

    args.array = sem_val;

    if (semctl(semid_, 0, SETALL, args) < 0) {
        tmp_errno = errno;
        mempool::MemPool::getInstance()->Free(sem_val);
        return _errno2ret(tmp_errno);
    }
    mempool::MemPool::getInstance()->Free(sem_val);
    init_flag_ = true;
    return IpcRet::SUCCESS;
}

IpcRet SemSysV::Destory()
{
    int tmp_errno;
    if (semid_ < 0) {
        semid_ = semget(key_, 0, 0);
        if (semid_ < 0) {
            tmp_errno = errno;
            IPC_ERROR("%s", strerror(tmp_errno));
            return _errno2ret(tmp_errno);
        }
    }
    if (semctl(this->semid_, 0, IPC_RMID) < 0) {
        tmp_errno = errno;
        IPC_ERROR("%s", strerror(tmp_errno));
        return _errno2ret(tmp_errno);
    }
    semid_ = -1;
    init_flag_ = false;
    return IpcRet::SUCCESS;
}

IpcRet SemSysV::Open(IpcMode mode)
{
    if (semid_ > 0) {
        return IpcRet::SUCCESS;
    }
    mode_t smode = 0;
    if (mode | IpcMode::READ_ONLY) {
        smode |= 0x04;
    } else if (mode | IpcMode::WRITE_ONLY) {
        smode |= 0x02;
    } else if (mode | IpcMode::READ_WRITE) {
        smode |= 0x06;
    } else {
        return IpcRet::SHM_EMODE;
    }

    semid_ = semget(key_, 0, smode);
    if (semid_ < 0) {
        int tmp_errno = errno;
        IPC_ERROR("%s", strerror(tmp_errno));
        return _errno2ret(tmp_errno);
    }
    init_flag_ = true;
    return IpcRet::SUCCESS;
}

IpcRet SemSysV::Close()
{
    if (semid_ > 0 || init_flag_) {
        semid_ = -1;
        init_flag_ = false;
    }
    return IpcRet::SUCCESS;
}

IpcRet SemSysV::_p(size_t sem_index, unsigned int num, util::time::Time* overtime)
{
    struct sembuf ops;
    memset(&ops, 0, sizeof(struct sembuf));

    ops.sem_num = 0;
    ops.sem_op = (0 - num);
    if (nonblock_flag_) {
        ops.sem_flg |= IPC_NOWAIT;
    } else {
        ops.sem_flg &= ~IPC_NOWAIT;
    }
    return IpcRet::SUCCESS;
}

IpcRet SemSysV::_v(size_t sem_index, unsigned int num)
{
    return IpcRet::SUCCESS;
}

#if 0
//private
//
/**
* @brief _p - Preemptive semaphore resources.
*
* @param [sem_index] - Semaphore set index
* @param [op_num] - Resource number
* @param [over_time] - Overtime time.If NULL then function will block until get sem resource.
*                      If not NULL but tv_sec and t_nsec is 0,function will non-block.
*
* @returns  IpcRet
*/
IpcRet SemSysV::_p(unsigned short sem_index, unsigned short op_num, struct timespec* over_time)
{
    int tmp_errno = 0;
    struct sembuf ops;
    struct timespec otime;
    struct timespec* p_otime;
    struct timespec first_time;
    struct timespec second_time;

    memset(&ops, 0x00, sizeof(struct sembuf));
    memset(&otime, 0x00, sizeof(struct timespec));

    ops.sem_num = sem_index;
    ops.sem_op = -1;
    if (over_time) {
        memcpy(&otime, over_time, sizeof(struct timespec));
        ops.sem_flg = ((!otime.tv_sec) && (!otime.tv_nsec)) ? IPC_NOWAIT : 0;
        p_otime = &otime;
    } else {
        ops.sem_flg = 0;
        p_otime = NULL;
    }

    clock_gettime(CLOCK_REALTIME, &first_time);
    do {
        if (semtimedop(this->semid_, &ops, op_num, p_otime)) {
            tmp_errno = errno;
            if (tmp_errno == EAGAIN && (!(ops.sem_flg & IPC_NOWAIT))) {
                return IpcRet::ETIMEOUT;
            } else if (tmp_errno == EINTR) {
                if (p_otime) {
                    clock_gettime(CLOCK_REALTIME, &second_time);
                    p_otime->tv_sec -= (second_time.tv_sec - first_time.tv_sec);
                    p_otime->tv_nsec -= (second_time.tv_nsec - first_time.tv_nsec);
                    p_otime->tv_sec = p_otime->tv_sec < 0 ? 0 : p_otime->tv_sec;
                    p_otime->tv_nsec = p_otime->tv_nsec < 0 ? 0 : p_otime->tv_nsec;
                    memcpy(&first_time, &second_time, sizeof(struct timespec));
                }
            } else {
                break;
            }
        } else {
            return IpcRet::SUCCESS;
        }
    } while ((!p_otime) || ((p_otime->tv_sec) || (p_otime->tv_nsec)));
    return _errno2ret(tmp_errno);
}

/**
* @brief _v - Free semaphore resources.
*
* @param [sem_index] - Semaphore set index
* @param [op_num] - Resource number
*
* @returns  IpcRet
*/
IpcRet SemSysV::_v(unsigned short sem_index, unsigned short op_num)
{
    int tmp_errno = 0;
    struct sembuf ops;

    memset(&ops, 0x00, sizeof(struct sembuf));

    ops.sem_num = op_num;
    ops.sem_op = 1;
    ops.sem_flg = 0;

    semop(this->semid_, &ops, op_num);
    tmp_errno = errno;
    return _errno2ret(tmp_errno);
}
#endif

} //namespace ipc
