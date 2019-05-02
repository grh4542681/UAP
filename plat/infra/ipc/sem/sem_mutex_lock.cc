#include "sem_mutex_lock"

namespace ipc::sem {

SemMutexLock::SemMutexLock()
{
}

SemMutexLock::SemMutexLock(std::string path)
{
}

SemMutexLock::~SemMutexLock()
{
}

template < typename T = SemSysV > IpcRet SemMutexLock::Create()
{
}

template < typename T = SemSysV > IpcRet SemMutexLock::Create(mode_t mode)
{
}

IpcRet SemMutexLock::Destroy()
{
}

template < typename T = SemSysV > IpcRet SemMutexLock::Open()
{
}

template < typename T = SemSysV > IpcRet SemMutexLock::Open(IpcMode mode)
{
}

IpcRet SemMutexLock::Close()
{
}

IpcRet SemMutexLock::Lock(util::time::Time* overtime)
{
}

IpcRet SemMutexLock::UnLock()
{
}

}
