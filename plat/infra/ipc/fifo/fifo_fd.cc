#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "ipc_log.h"
#include "ipc_return.h"
#include "ipc_fd_type.h"
#include "fifo_fd.h"

namespace ipc::fifo {

FifoFD::FifoFD()
{
    fd_ = -1;
    init_flag_ = false;
}

FifoFD::FifoFD(int fd)
{
    fd_type_ = IpcFDType::FIFO;
    struct stat fd_stat;
    if (fstat(fd, &fd_stat)) {
        int temp_errno = errno;
        IPC_ERROR("%s", strerror(temp_errno));
        init_flag_ = false;
        return;
    }
    if (!S_ISFIFO(fd_stat.st_mode)) {
        IPC_ERROR("fd[%d] not a fifo fd", fd);
        init_flag_ = false;
        return;
    }
    fd_ = fd;
}

FifoFD::FifoFD(const FifoFD& other) : IpcFD(other)
{
    fd_ = other.fd_; 
}

FifoFD::~FifoFD()
{
    
}

void FifoFD::Close()
{
    if (init_flag_) {
        close(fd_);
        init_flag_ = false;
    }
}

int FifoFD::Read(void* data, unsigned int datalen)
{

}

int FifoFD::Write(const void* data, unsigned int datalen)
{

}

FifoFD& FifoFD::operator= (const FifoFD& other)
{
    IpcFD::operator= (other);
    fd_ = other.fd_;
    return *this;
}

}
