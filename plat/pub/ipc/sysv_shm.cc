#include "sysv_shm.h"

namespace ipc {

SysVShm::SysVShm(key_t key, size_t size)
{

}

SysVShm::SysVShm(key_t key, size_t size, mode_t mode)
{

}

SysVShm::~SysVShm()
{

}

static key_t SysVShm::GenKey(const char *pathname, int proj_id)
{
    return ftok(pathname, proj_id);
}

IpcRet SysVShm::At()
{

}

IpcRet SysVShm::Dt()
{

}

IpcRet SysVShm::Write(void* data, void* datalen)
{

}

IpcRet SysVShm::Write(void* pstart, void* data, void* datalen)
{

}

IpcRet SysVShm::Read(void* data, void* datalen)
{

}

IpcRet SysVShm::Read(void* pstart, void* data, void* datalen)
{

}

IpcRet SysVShm::Create()
{

}

IpcRet SysVShm::Destory()
{

}

//private
IpcRet SysVShm::_write(void* pstart, void* data, unsigned int datalen)
{

}

IpcRet SysVShm::_read(void* pstart, void* data, unsigned int datalen)
{

}

} //namespace end