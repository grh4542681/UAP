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


namespace base {
//public
/*
 * This function is constructor.
 * param:
 *      key : The key of semaphore set.
 *      semnum : How many semaphore you want created in semaphore set,default is 1.
 *      mode : Access permission of semaphore set,default is 0666.
 *      semval : semaphore init value,default is 0.
 */
SysVSem::SysVSem(key_t key){
    this->key_ = key;
    this->semnum_ = 1;
    this->mode_ = 0666;
    this->semval_ = 0;
    this->init_flag_ = 0;
}

SysVSem::SysVSem(key_t key, unsigned int semnum, mode_t mode, unsigned short semval){
    this->key_ = key;
    this->semnum_ = semnum;
    this->mode_ = mode;
    this->semval_ = semval;
    this->init_flag_ = 0;
}

/*
 * This function is destructor.
 */
SysVSem::~SysVSem(){

}

key_t SysVSem::GenKey(const char *pathname, int proj_id){
    return ftok(pathname, proj_id);
}

IpcRet SysVSem::Grab(unsigned int timeout){
    return Grab(0, timeout);
}

IpcRet SysVSem::Grab(unsigned int semnum, unsigned int timeout){

}

//private
/*
 * This function is private.Its function is create a semaphore set.
 * If the semaphore set abort the key was already exists,it will be
 * return error.
 */
IpcRet SysVSem::_create(){
    int ret;
    int loop;
    int tmp_errno;
    unsigned short* ptr;
    SemUn args;

    //If this semaphore set already created by this, just return.
    if (this->init_flag_) {
        return IpcRet::SUCCESS;
    }

    if ((ret = semget(this->key_, this->semnum_, (this->mode_)|IPC_CREAT|IPC_EXCL)) == -1) {
        tmp_errno = errno;
        SEM_ERROR("%s", strerror(tmp_errno));
        return _errno2ret(tmp_errno);
    }
    this->semid_ = ret;

    ptr = (short unsigned int*)malloc(this->semnum_ * sizeof(unsigned short));
    if (!ptr) {
        return IpcRet::EMALLOC;
    }

    for (loop = 0; loop < this->semnum_; loop++) {
        ptr[loop] = this->semval_;
    }
    args.array_ = ptr;

    if ((ret = semctl(this->semid_, 0, SETALL, args)) == -1) {
        tmp_errno = errno;
        free(ptr);
        return _errno2ret(tmp_errno);
    }
    free(ptr);
    this->init_flag_ = 1;

    return IpcRet::SUCCESS;
}

/*
 * This function is destroy the semaphore set
 */
IpcRet SysVSem::_destroy(){
    int ret;
    int tmp_errno;
    if ((ret = semctl(this->semid_, 0, IPC_RMID)) == -1) {
        tmp_errno = errno;
        SEM_ERROR("%s", strerror(tmp_errno));
        return _errno2ret(tmp_errno);
    }
    this->init_flag_ = 0;
    return IpcRet::SUCCESS;
}

IpcRet SysVSem::_getid(){

}

} //namespace base
