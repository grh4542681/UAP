#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>

#include "ipc_return.h"
#include "ipc_log.h"
#include "sysv_sem.h"


namespace ipc {
//public
//
/**
* @brief SysVSem - This function is constructor.
*
* @param [key] - The key of semaphore set.
*/
SysVSem::SysVSem(key_t key) : key_(key){
    this->semnum_ = 1;
    this->mode_ = 0666;
    this->semval_ = 1;
    this->init_flag_ = 0;
}

/**
* @brief SysVSem - This function is constructor.
*
* @param [key] - The key of semaphore set.
* @param [semnum] - How many semaphore you want created in semaphore set,default is 1.
* @param [mode] - Access permission of semaphore set,default is 0666.
* @param [semval] - semaphore init value,default is 0.
*/
SysVSem::SysVSem(key_t key, unsigned short semnum, mode_t mode, unsigned short semval)
                    : key_(key), semnum_(semnum), mode_(mode), semval_(semval){
    this->init_flag_ = 0;
}

/**
* @brief ~SysVSem - This function is destructor.
*/
SysVSem::~SysVSem(){
}

key_t SysVSem::GenKey(const char *pathname, int proj_id){
    return ftok(pathname, proj_id);
}

IpcRet SysVSem::P()
{
    return _p(0, 1, NULL);
}

IpcRet SysVSem::P(struct timespec* over_time)
{
    return _p(0, 1, over_time);
}

IpcRet SysVSem::P(unsigned short op_num)
{
    return _p(0, op_num, NULL);
}

IpcRet SysVSem::P(unsigned short op_num, struct timespec* over_time)
{
    return _p(0, op_num, over_time);
}

IpcRet SysVSem::P(unsigned short sem_index, unsigned short op_num, struct timespec* over_time)
{
    return _p(sem_index, op_num, over_time);
}

IpcRet SysVSem::V()
{
    return _v(0, 1);
}

IpcRet SysVSem::V(unsigned short op_num)
{
    return _v(0, op_num);
}

IpcRet SysVSem::V(unsigned short sem_index, unsigned short op_num)
{
    return _v(sem_index, op_num);
}

/**
* @brief _create - Its function is create a semaphore set.If the 
*                  semaphore set abort the key was already exists,
*                  it will be return error
*
* @returns  IpcRet
*/
rm::RmRet SysVSem::create()
{
    int ret;
    int loop;
    int tmp_errno;
    unsigned short* ptr;
    SemUn args;

    if ((ret = semget(this->key_, this->semnum_, (this->mode_)|IPC_CREAT)) == -1) {
        tmp_errno = errno;
        SEM_ERROR("%s", strerror(tmp_errno));
        return rm::RmRet::ERROR;
    }
    this->semid_ = ret;

    ptr = (short unsigned int*)malloc(this->semnum_ * sizeof(unsigned short));
    if (!ptr) {
        return rm::RmRet::ERROR;
    }

    for (loop = 0; loop < this->semnum_; loop++) {
        ptr[loop] = this->semval_;
    }
    args.array_ = ptr;

    if ((ret = semctl(this->semid_, 0, SETALL, args)) == -1) {
        tmp_errno = errno;
        free(ptr);
        return rm::RmRet::ERROR;
    }
    free(ptr);
    SEM_DEBUG("Create semaphore,semid [%d]", this->semid_);
    this->init_flag_ = 1;

    return rm::RmRet::SUCCESS;
}

/*
 * This function is destroy the semaphore set
 */
rm::RmRet SysVSem::destory()
{
    int ret;
    int tmp_errno;
    if (this->init_flag_) {
        if ((ret = semctl(this->semid_, 0, IPC_RMID)) == -1) {
            tmp_errno = errno;
            SEM_ERROR("%s", strerror(tmp_errno));
            return rm::RmRet::ERROR;
        }
        SEM_DEBUG("Destroy semaphore,semid [%d]", this->semid_);
    }
    return rm::RmRet::SUCCESS;
}

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
IpcRet SysVSem::_p(unsigned short sem_index, unsigned short op_num, struct timespec* over_time)
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
IpcRet SysVSem::_v(unsigned short sem_index, unsigned short op_num)
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

} //namespace ipc
