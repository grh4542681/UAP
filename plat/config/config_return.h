#ifndef __CONFIG_RETURN_H__
#define __CONFIG_RETURN_H__

namespace config {

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
