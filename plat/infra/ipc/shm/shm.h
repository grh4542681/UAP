/*******************************************************
 * Copyright (C) For free.
 * All rights reserved.
 *******************************************************
 * @author   : Ronghua Gao
 * @date     : 2019-04-22 13:17
 * @file     : shm.h
 * @brief    : Base shm virtual class.
 * @note     : Email - grh4542681@163.com
 * ******************************************************/
#ifndef __SHM_H__
#define __SHM_H__

#include <string>
#include <sys/types.h>

#include "ipc_return.h"
#include "ipc_mode.h"
#include "shm_status.h"

namespace ipc::shm {

/**
* @brief - Top share memory virtual class
*/
class Shm {
public:
    /**
    * @brief Shm - Constructor.
    */
    Shm() {
        path_.clear();
        head_ = NULL;
        size_ = 0;
        status_ = ShmStatus::UNKNOW;
    }

    /**
    * @brief Shm - Constructor.
    *
    * @param [path] - Share memory key(path).
    */
    Shm(std::string path) {
        path_ = path;
        head_ = NULL;
        size_ = 0;
    }

    /**
    * @brief ~Shm - Destructor.
    */
    virtual ~Shm() { }

    /**
    * @brief Create - Create share memory.
    *
    * @param [mode] - Share memory access mode.
    * @param [size] - Share memory total size.
    *
    * @returns  IpcRet.
    */
    virtual IpcRet Create(mode_t mode, size_t size) { return IpcRet::SUCCESS; }

    /**
    * @brief Destroy - Destroy share memory.
    *
    * @returns  IpcRet.
    */
    virtual IpcRet Destroy() { return IpcRet::SUCCESS; }

    /**
    * @brief Open - Open a share memory.
    *
    * @param [mode] - Share memory read-write mode.
    *
    * @returns  IpcRet.
    */
    virtual IpcRet Open(IpcMode mode) { return IpcRet::SUCCESS; }

    /**
    * @brief Close - Close a share memory.
    *
    * @returns  IpcMode.
    */
    virtual IpcRet Close() { return IpcRet::SUCCESS; }

    /**
    * @brief Sync - Sync cache to share memory.
    *
    * @returns  
    */
    virtual IpcRet Sync() { return IpcRet::SUCCESS; }

    /**
    * @brief GetHeadPtr - Get share memory head pointer.
    *
    * @returns  IpcRet.
    */
    void* GetHeadPtr() {
        return head_;
    }
protected:
    std::string path_;  ///< Share memory key(path).
    size_t size_;       ///< Share memory size.
    void* head_;        ///< Share memory pointer.
    ShmStatus status_;  ///< Share memory status.

    Shm(const Shm& other) {
        path_ = other.path_;
        head_ = head_;
        size_ = other.size_;
    }
};

}

#endif
