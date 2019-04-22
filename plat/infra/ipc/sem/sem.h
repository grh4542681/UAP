#ifndef __SEM_H__
#define __SEM_H__

#include <sys/types.h>
#include <string>

#include "time/vtime.h"
#include "ipc_return.h"
#include "ipc_mode.h"

namespace ipc::sem {

class Sem {
public:
    Sem(std::string path) {
        path_ = path;
        nonblock_flag_ = false;
        init_flag_ = false;
    }
    Sem() {
        nonblock_flag_ = false;
        init_flag_ = false;
    }
    virtual ~Sem() { }

    virtual IpcRet Create(mode_t mode) { return IpcRet::SUCCESS; }
    virtual IpcRet Destroy() { return IpcRet::SUCCESS; }
    virtual IpcRet Open(IpcMode mode) { return IpcRet::SUCCESS; }
    virtual IpcRet Close() { return IpcRet::SUCCESS; }

    virtual IpcRet V(unsigned int num, util::time::Time* overtime) { return IpcRet::SUCCESS; }
    virtual IpcRet P(unsigned int num) { return IpcRet::SUCCESS; }
    IpcRet V(util::time::Time* overtime) {
        return V(1, overtime);
    }
    IpcRet P() {
        return P(1);
    }

    bool SetNonBlock(bool flag) {
        nonblock_flag_ = flag;
        return this->nonblock_flag_;
    }

protected:
    std::string path_;
    bool nonblock_flag_;
    bool init_flag_;

    Sem(const Sem& other) {
        path_ = other.path_;
        nonblock_flag_ = other.nonblock_flag_;
        init_flag_ = false;
    }
};

}

#endif
