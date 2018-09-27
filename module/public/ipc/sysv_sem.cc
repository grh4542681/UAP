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
SysVSem::SysVSem(key_t key, unsigned int semnum = 1, mode_t mode = 0666, unsigned short semval = 0){
    this->key_ = key;
    this->semnum_ = semnum;
    this->mode_ = mode;
    this->semval_ = semval;
}

SysVSem::~SysVSem(){

}

IpcRet SysVSem::Grab(unsigned int timeout){
    return Grab(0, timeout);
}

IpcRet SysVSem::Grab(unsigned int semnum, unsigned int timeout){

}

//private
IpcRet SysVSem::_create(){
    int ret;
    int loop;
    int tmp_errno;
    unsigned short* ptr;
    SemUn args;

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

IpcRet SysVSem::_destroy(){

}

IpcRet SysVSem::_getid(){

}

} //namespace base
