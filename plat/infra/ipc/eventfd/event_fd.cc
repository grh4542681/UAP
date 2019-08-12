#include "mempool.h"

#include "event_fd.h"

namespace ipc::eventfd {

EventFD::EventFD()
{

}

EventFD::EventFD(unsigned int fd, bool auto_close)
{

}

EventFD::EventFD(EventFD& other)
{

}

EventFD::~EventFD()
{

}

ret::Return EventFD::SetFD(unsigned int fd, bool auto_close)
{
    return IpcRet::SUCCESS;
}

ret::Return EventFD::Dup(io::FD& new_fd)
{
    return IpcRet::SUCCESS;
}

io::FD* EventFD::Clone()
{
    return mempool::MemPool::getInstance()->Malloc<EventFD>(*this);
}

void EventFD::Close()
{

}

size_t EventFD::Write(const void* data, size_t datalen)
{
    return 0;
}

size_t EventFD::Read(void* data, size_t datalen)
{
    return 0;
}

bool EventFD::IsCloexec()
{
    return (efd_flag_ | EventFD::CLOEXEC);
}

bool EventFD::IsNonblock()
{
    return (efd_flag_ | EventFD::NONBLOCK);
}

bool EventFD::IsSemaphore()
{
    return (efd_flag_ | EventFD::SEMAPHORE);
}

void EventFD::SetEfdFlag(int flag)
{
    efd_flag_ = flag;
}

}
