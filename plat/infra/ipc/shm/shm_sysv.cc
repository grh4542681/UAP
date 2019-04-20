#include "shm_sysv.h"

namespace ipc {

ShmSysV::ShmSysV(key_t key, size_t size)
{

}

ShmSysV::ShmSysV(key_t key, size_t size, mode_t mode)
{

}

ShmSysV::~ShmSysV()
{

}

IpcRet ShmSysV::At()
{

}

IpcRet ShmSysV::Dt()
{

}

IpcRet ShmSysV::Write(void* data, void* datalen)
{

}

IpcRet ShmSysV::Write(void* pstart, void* data, void* datalen)
{

}

IpcRet ShmSysV::Read(void* data, void* datalen)
{

}

IpcRet ShmSysV::Read(void* pstart, void* data, void* datalen)
{

}

IpcRet ShmSysV::Create()
{

}

IpcRet ShmSysV::Destory()
{

}

//private
IpcRet ShmSysV::_write(void* pstart, void* data, unsigned int datalen)
{

}

IpcRet ShmSysV::_read(void* pstart, void* data, unsigned int datalen)
{

}

} //namespace end
