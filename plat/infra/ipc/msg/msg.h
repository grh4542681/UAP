#ifndef __MSG_H__
#define __MSG_H__

#include <string>

namespace ipc::msg {

class Msg {
public:
    Msg() {
        path_.clear();
    }

    Msg(std::string path) {
        path_ = path;
    }

    virtual ~Msg() { }

    std::string GetPath() {
        return path_;
    }

    virtual IpcRet Create(size_t size, mode_t mode) { return IpcRet::ESUBCLASS; }
    virtual IpcRet Destroy() { return IpcRet::ESUBCLASS; }
    virtual IpcRet Open(IpcMode mode) { return IpcRet::ESUBCLASS; }
    virtual IpcRet Close() { return IpcRet::ESUBCLASS; }

private:
    std::string path_;
};

}

#endif
