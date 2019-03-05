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

/**
* @brief - Socket api return value.
*/
enum class SockRet: int {
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
    SOCK_LINKDOWN,      ///< link down.
    SOCK_EACCES,        ///< errno EACCES.
    SOCK_EAFNOSUPPORT,  ///< errno EAFNOSUPPORT.
    SOCK_EINVAL,        ///< errno EINVAL.
    SOCK_EMFILE,        ///< errno EMFILE.
    SOCK_ENFILE,        ///< errno ENFILE.
    SOCK_ENOBUFS,       ///< errno ENOBUFS.
    SOCK_ENOMEM,        ///< errno ENOMEM.
    SOCK_EPROTONOSUPPORT,   ///< errno EPROTONOSUPPORT.
    SOCK_EADDRINUSE,    ///< errno EADDRINUSE.
    SOCK_EBADF,         ///< errno EBADF.
    SOCK_ENOTSOCK,      ///< errno ENOTSOCK.
    SOCK_EOPNOTSUPP,    ///< errno EOPNOTSUPP.
    SOCK_EAGAIN,        ///< errno EAGAIN.

};

} // namespace sock

#endif
