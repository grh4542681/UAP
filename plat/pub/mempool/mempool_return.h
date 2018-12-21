#ifndef __MEMPOOL_RETURN_H__
#define __MEMPOOL_RETURN_H__

namespace pub{

typedef enum class _MempoolRet: int {
//common return val
    SUCCESS = 0x00,
    ERROR,
    EMALLOC,
    EINIT,
    ETIMEOUT,

    EUNKOWNERRNO,
} MempoolRet;

} // namespace base

#endif
