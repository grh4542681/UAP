/*******************************************************
 * Copyright (C) For free.
 * All rights reserved.
 *******************************************************
 * @author   : Ronghua Gao
 * @date     : 2019-04-22 13:43
 * @file     : shm_sysv.h
 * @brief    : SystemV share memory.
 * @note     : Email - grh4542681@163.com
 * ******************************************************/
#ifndef __SHM_SYSV_H__
#define __SHM_SYSV_H__

#include <sys/types.h>
#include <sys/shm.h>

#include "ipc_log.h"
#include "ipc_return.h"
#include "shm.h"

namespace ipc::shm {

/**
* @brief - SystemV share memory.
*/
class ShmSysV : public Shm {
public:
    /**
    * @brief ShmSysV - Constructor.
    *
    * @param [path] - Share memory key.
    */
    ShmSysV(std::string path);

    /**
    * @brief ShmSysV - Constructor
    */
    ShmSysV();

    /**
    * @brief ~ShmSysV - Destructor.
    */
    ~ShmSysV();

    /**
    * @brief Create - Create share memory.
    *
    * @param [mode] - Share memory access mode.
    * @param [size] - Share memory size.
    *
    * @returns  IpcRet.
    */
    IpcRet Create(mode_t mode, size_t size);

    /**
    * @brief Destroy - Destroy share memory.
    *
    * @returns  IpcRet.
    */
    IpcRet Destroy();

    /**
    * @brief Open - Open share memory.
    *
    * @param [mode] - Share memory read-write mode.
    *
    * @returns  IpcRet.
    */
    IpcRet Open(IpcMode mode);

    /**
    * @brief Close - Close share memory.
    *
    * @returns  IpcRet.
    */
    IpcRet Close();

    /**
    * @brief Sync - Sync cache to share memory.(system v no use).
    *
    * @returns  IpcRet.
    */
    IpcRet Sync();

private:
    key_t key_; ///< SystemV ipc key.
    int shmid_; ///< SystemV shm id.

    ShmSysV(const ShmSysV& other);

    static IpcRet _errno2ret(int ierrno)
    {   
        switch (ierrno) {
            case 0:
                return IpcRet::SUCCESS;
            case EACCES:
                return IpcRet::SHM_EACCES;
            case EEXIST:
                return IpcRet::SHM_EEXIST;
            case EINVAL:
                return IpcRet::SHM_EINVAL;
            case ENFILE:
                return IpcRet::SHM_ENFILE;
            case ENOENT:
                return IpcRet::SHM_ENOENT;
            case ENOMEM:
                return IpcRet::SHM_ENOMEM;
            case ENOSPC:
                return IpcRet::SHM_ENOSPC;
            case EPERM:
                return IpcRet::SHM_EPERM;
            default:
                return IpcRet::EUNKOWNERRNO;
        }   
    }   

    static int _ret2errno(IpcRet ret)
    {   
        switch (ret) {
            case IpcRet::SUCCESS:
                return 0;
            case IpcRet::SHM_EACCES:
                return EACCES;
            case IpcRet::SHM_EEXIST:
                return EEXIST;
            case IpcRet::SHM_EINVAL:
                return EINVAL;
            case IpcRet::SHM_ENFILE:
                return ENFILE;
            case IpcRet::SHM_ENOENT:
                return ENOENT;
            case IpcRet::SHM_ENOMEM:
                return ENOMEM;
            case IpcRet::SHM_ENOSPC:
                return ENOSPC;
            case IpcRet::SHM_EPERM:
                return EPERM;
            default:
                return (-1);
        }   
    }
    
};

}//namespace ipc end

#endif
