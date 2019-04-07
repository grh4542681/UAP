#include "fifo_fd.h"
#include "ipc_fd_type.h"

namespace ipc::fifo {

FifoFD::FifoFD(int fd)
{
    fd_type_ = IpcFDType::FIFO;
}

FifoFD::~FifoFD()
{
    
}

}