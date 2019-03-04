/*******************************************************
 * Copyright (C) For free.
 * All rights reserved.
 *******************************************************
 * @author   : Ronghua Gao
 * @date     : 2019-03-04 09:59
 * @file     : sock_return.h
 * @brief    : Socket return value header.
 * @note     : Email - grh4542681@163.com
 * ******************************************************/
#ifndef __SOCK_RETURN_H__
#define __SOCK_RETURN_H__

namespace sock{

typedef enum class _SockRet: int {
//common return val
    SUCCESS = 0,        ///< success.
    ERROR = -999,       ///< error.
    EMALLOC,            ///< malloc error.
    EINIT,              ///< init check error.
    EBADARGS,           ///< bad arguments.
    ETIMEOUT,           ///< time out.
    ENONSUPPORT,        ///< not support.
    EUNKOWNERRNO,       ///< unknow error.

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
