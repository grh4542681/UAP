/*******************************************************
 * Copyright (C) For free.
 * All rights reserved.
 *******************************************************
 * @author   : Ronghua Gao
 * @date     : 2019-03-04 09:04
 * @file     : thread_return.h
 * @brief    : Thread return value header.
 * @note     : Email - grh4542681@163.com
 * ******************************************************/
#ifndef __THREAD_RETURN_H__
#define __THREAD_RETURN_H__

#include <errno.h>

namespace thread{

enum class ThreadRet: int {
//common return val
    SUCCESS = 0,    ///< sucess.
    ERROR = -999,   ///< error.
    EMALLOC,        ///< malloc error.
    EINIT,          ///< check init error.
    EBADARGS,       ///< bad arguments.
    ETIMEOUT,       ///< time out.
    EUNKOWNERRNO,   ///< unknow error.

//thread info
    THREAD_EREGISTER,
    THREAD_EUNREGISTER,

//thread single
    THREAD_ERUNNING,

//thread signal
    THREAD_ESIGNALMASKTYPE,
    THREAD_ESIGNALMASK,
};

} // namespace THREAD

#endif
