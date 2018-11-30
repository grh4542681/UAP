#ifndef __SOCK_RETURN_H__
#define __SOCK_RETURN_H__

namespace sock{

typedef enum class _SockRet: int {
//common return val
    SUCCESS = 0x00,
    ERROR,
    EMALLOC,
    EINIT,
    ETIMEOUT,
    EUNKOWNERRNO,

//socket
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

} SockRet;

} // namespace sock

#endif
