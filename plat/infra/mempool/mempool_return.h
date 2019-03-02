#ifndef __MEMPOOL_RETURN_H__
#define __MEMPOOL_RETURN_H__

namespace pub{

/**
 * @brief Memory pool return value.
 * 
 */
enum class MempoolRet: int {
//common return val
    SUCCESS = 0,
    ERROR = -999,
    EMALLOC,
    EINIT,
    ETIMEOUT,

    EUNKOWNERRNO,
};

} // namespace mempool

#endif
