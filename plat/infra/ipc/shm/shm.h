#ifndef __SHM_H__
#define __SHM_H__

#include <string>
#include <sys/types.h>

#include "ipc_return.h"
#include "shm_mode.h"

namespace ipc::shm {

class Shm {
public:
    Shm() {
        path_.clear();
        head_ = NULL;
        size_ = 0;
    }
    Shm(std::string path) {
        path_ = path;
        head_ = NULL;
        size_ = 0;
    }
    virtual ~Shm() { }

    virtual IpcRet Create(mode_t mode, size_t size) { return IpcRet::SUCCESS; }
    virtual IpcRet Destroy() { return IpcRet::SUCCESS; }
    virtual IpcRet Open(ShmMode mode) { return IpcRet::SUCCESS; }
    virtual IpcRet Close() { return IpcRet::SUCCESS; }
    virtual IpcRet Sync() { return IpcRet::SUCCESS; }

    void* GetHeadPtr() {
        return head_;
    }
protected:
    std::string path_;
    size_t size_;
    void* head_;

    Shm(const Shm& other) {
        path_ = other.path_;
        head_ = head_;
        size_ = other.size_;
    }
};

}

#endif
