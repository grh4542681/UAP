#ifndef __DM_RETURN_H__
#define __DM_RETURN_H__

namespace dm {

enum class DmRet: int {
//common return val
    SUCCESS = 0,        ///< success.
    ERROR = -999,       ///< error.
    EMALLOC,            ///< malloc error.
    EINIT,              ///< init check error.
    EBADARGS,           ///< bad arguments.
    ETIMEOUT,           ///< time out.
    ENONSUPPORT,        ///< not support.
    EUNKOWNERRNO,       ///< unknow error.

};

}

#endif
