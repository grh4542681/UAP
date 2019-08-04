#ifndef __IPC_RETURN_H__
#define __IPC_RETURN_H__

#include "return.h"

namespace ipc {

class IpcRet : public ret::Return {
public:
    enum ECode{
        // fifo return val
        FIFO_ESOCKPAIR,

        // shm return val
        SHM_EMODE,
        SHM_ECREATED,

        // sem return val
        SEM_EMODE,
        SEM_ENOTFOUND,

        // sem rw lock
        SEM_ELOCKED,

        // shm list return val
        SL_ENOSPACE,
        SL_EBITMAP,

        // msg shm return val
        MSG_ENOSPACE,
    };
public:
    static ECodeMapType ECodeMap;
public:
    IpcRet(int err_code) : ret::Return(err_code) {
        err_code_vec_.push_back(&IpcRet::ECodeMap);
    }
    ~IpcRet() { };
};

}

#endif