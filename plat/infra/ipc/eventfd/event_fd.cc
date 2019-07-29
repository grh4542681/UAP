#include "mempool.h"

#include "event_fd.h"

namespace ipc::eventfd {

EventFD::EventFD(int flag)
{

}

EventFD::~EventFD()
{

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

}
