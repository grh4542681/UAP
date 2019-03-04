/*******************************************************
 * Copyright (C) For free.
 * All rights reserved.
 *******************************************************
 * @author   : Ronghua Gao
 * @date     : 2019-03-04 09:01
 * @file     : parser_return.h
 * @brief    : Parser return value header.
 * @note     : Email - grh4542681@163.com
 * ******************************************************/
#ifndef __PARSER_RETURN_H__
#define __PARSER_RETURN_H__

namespace parser{

/**
* @brief - Parser return value.
*/
typedef enum class _ParserRet: int {
//common return val
    SUCCESS = 0x00, ///< success.
    ERROR,          ///< error.
    EMALLOC,        ///< malloc error.
    EINIT,          ///< init check error.
    ETIMEOUT,       ///< time out.
    EBADARGS,       ///< bad arguments.
    ENOTFOUND,      ///< not found.
    ELOCK,          ///< lock error.
    EGETRLOCK,      ///< get read lock error.
    EGETWLOCK,      ///< get write lock error.
    EUNLOCK,        ///< release lock error.
    EMAHTYPE,       ///< field type not match.

    EUNKOWNERRNO,   ///< unknow error.

} ParserRet;

} // namespace parser

#endif
