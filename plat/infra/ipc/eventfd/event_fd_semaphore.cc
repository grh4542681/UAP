#include "event_fd_semaphore.h"

namespace ipc::eventfd {

SemEventFD::SemEventFD()
{
}

SemEventFD::SemEventFD(std::string name)
{
}

SemEventFD::~SemEventFD()
{
}

EventFD& SemEventFD::GetEFD()
{
    return fd_;
}

bool SemEventFD::IsExist()
{
    return true;
}

IpcRet SemEventFD::Create([[maybe_unused]] size_t semnum, [[maybe_unused]] mode_t mode)
{
    return IpcRet::SUCCESS;
}

IpcRet SemEventFD::Destroy()
{
    return IpcRet::SUCCESS;
}

IpcRet SemEventFD::_p(size_t sem_index, timer::Time* overtime)
{
    return IpcRet::SUCCESS;
}

IpcRet SemEventFD::_v(size_t sem_index)
{
    return IpcRet::SUCCESS;
}

}
