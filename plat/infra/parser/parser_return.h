#ifndef __PARSER_RETURN_H__
#define __PARSER_RETURN_H__

namespace parser{

typedef enum class _ParserRet: int {
//common return val
    SUCCESS = 0x00,
    ERROR,
    EMALLOC,
    EINIT,
    ETIMEOUT,
    EBADARGS,
    ENOTFOUND,
    ELOCK,
    EGETRLOCK,
    EGETWLOCK,
    EUNLOCK,
    EMAHTYPE,

    EUNKOWNERRNO,

} ParserRet;

} // namespace parser

#endif
