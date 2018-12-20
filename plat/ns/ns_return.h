#ifndef __NS_RETURN_H__
#define __NS_RETURN_H__

namespace ns{

typedef enum class _NsRet: int {
//common return val
    SUCCESS = 0x00,
    ERROR,
    EMALLOC,
    EINIT,
    ETIMEOUT,

    EUNKOWNERRNO,
} NsRet;

} // namespace base

#endif
