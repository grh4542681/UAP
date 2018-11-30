#ifndef __RM_RETURN_H__
#define __RM_RETURN_H__

namespace rm{

typedef enum class _RmRet: int {
//common return val
    SUCCESS = 0x00,
    ERROR,
    EMALLOC,
    EINIT,
    ETIMEOUT,

    EUNKOWNERRNO,
} RmRet;

} // namespace base

#endif
