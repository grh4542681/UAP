#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#include "ipc_return.h"
#include "sysv_sem.h"


namespace base {
//public
SysVSem::SysVSem(key_t key, unsigned int semnum = 1, mode_t mode = 0666, unsigned short semval = 0){
    this->key = key;
    this->semnum = semnum;
    this->mode = mode;
    this->semval = semval;
}

SysVSem::~SysVSem(){

}

IpcRet SysVSem::Grab(unsigned int timeout){
    return Grab(0, timeout);
}

IpcRet SysVSem::Grab(unsigned int semnum, unsigned int timeout){

}

//private
IpcRet SysVSem::Create(){
    int ret;
}

} //namespace base
