#ifndef __SHM_H__
#define __SHM_H__

#include <string>
#include <sys/types.h>

#include "ipc_return.h"

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
    Shm(const Shm& other) {
        path_ = other.path_;
        head_ = NULL;
        size_ = other.size_;
    }
    virtual ~Shm() { }

    virtual IpcRet Create(size_t size);
    virtual IpcRet Destroy();
    virtual IpcRet Open(ShmMode mode);
    virtual IpcRet Close();

    void* GetHeadPtr() {
        return head_;
    }
private:
    std::string path_;
    size_t size_;
    void* head_;
};

}

#endif