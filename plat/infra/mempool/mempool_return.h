#ifndef __MEMPOOL_RETURN_H__
#define __MEMPOOL_RETURN_H__

namespace mempool {

/**
 * @brief Memory pool return value.
 */
enum class MemPoolRet: int {
//common return val
    SUCCESS = 0,
    ERROR = -999,
    EMALLOC,
    EINIT,
    ETIMEOUT,
    EBADARGS,

//memort
    EALLOC,

//busy list
    EBUSYLISTINSERT,
    EBUSYLISTNOTFOUND,
    EBUSYLISTDUPADDRESS,

    EUNKOWNERRNO,
};

} // namespace mempool

#endif
