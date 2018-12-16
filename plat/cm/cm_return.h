#ifndef __CM_RETURN_H__
#define __CM_RETURN_H__

namespace cm{

typedef enum class _CmRet: int {
//common return val
    SUCCESS = 0x00,
    ERROR,
    EMALLOC,
    EINIT,
    EUNKOWNERRNO,
} CmRet;

} // namespace cm

#endif
