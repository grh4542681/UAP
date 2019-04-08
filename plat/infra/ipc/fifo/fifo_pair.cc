#include <sys/types.h>
#include <sys/socket.h>

#include "fifo_pair.h"

namespace ipc::fifo {

FifoPair::FifoPair()
{
    init_flag_ = false;
}

FifoPair::FifoPair(const FifoPair& other)
{
    init_flag_ = other.init_flag_;
    fds_[0] = other.fds_[0];
    fds_[1] = other.fds_[1];
    fds_[2] = other.fds_[2];
}

FifoPair::~FifoPair()
{
    if (init_flag_) {
        Close();
    }
}

IpcRet FifoPair::Open()
{
    int fds[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds)) {
        return IpcRet::FIFO_ESOCKPAIR;        
    }

    fds_[0] = FifoFD(fds[0]);
    fds_[1] = FifoFD(fds[1]);
    init_flag_ = true;

    return IpcRet::SUCCESS;
}

void FifoPair::Close()
{
    if (init_flag_) {
        fds_[0].Close();
        fds_[1].Close();
        init_flag_ = false;
    }
}

FifoFD& FifoPair::operator[] (const unsigned int index)
{
    if (index > 1) {
        IPC_ERROR("Bad index[%u] in pari fds", index);
        return fds_[2];
    }
    return fds_[index];
}

FifoPair& FifoPair::operator= (const FifoPair& other)
{
    init_flag_ = other.init_flag_;
    fds_[0] = other.fds_[0];
    fds_[1] = other.fds_[1];
    fds_[2] = other.fds_[2];
    return *this;
}

}
