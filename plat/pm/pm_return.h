#ifndef __PM_RETURN_H__
#define __PM_RETURN_H__

namespace pm{

typedef enum class _PmRet: int {
//common return val
    SUCCESS = 0x00,
    ERROR,
    EMALLOC,
    EINIT,
    ETIMEOUT,

    EUNKOWNERRNO,
} PmRet;

} // namespace base

#endif
