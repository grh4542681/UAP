#ifndef __SOCK_RETURN_H__
#define __SOCK_RETURN_H__

namespace sock{

typedef enum class _SockRet: int {
//common return val
    SUCCESS = 0,
    ERROR = -999,
    EMALLOC,
    EINIT,
    EBADARGS,
    ETIMEOUT,
    ENONSUPPORT,
    EUNKOWNERRNO,

//socket
    SOCK_LINKDOWN,
    SOCK_EACCES,
    SOCK_EAFNOSUPPORT,
    SOCK_EINVAL,
    SOCK_EMFILE,
    SOCK_ENFILE,
    SOCK_ENOBUFS,
    SOCK_ENOMEM,
    SOCK_EPROTONOSUPPORT,
    SOCK_EADDRINUSE,
    SOCK_EBADF,
    SOCK_ENOTSOCK,
    SOCK_EOPNOTSUPP,
    SOCK_EAGAIN,

} SockRet;

} // namespace sock

#endif
