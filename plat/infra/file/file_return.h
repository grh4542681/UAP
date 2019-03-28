#ifndef __FILE_RETURN_H__
#define __FILE_RETURN_H__

namespace file {

enum class FileRet: int {
//common return val
    SUCCESS = 0,        ///< success.
    ERROR = -999,       ///< error.
    EMALLOC,            ///< malloc error.
    EINIT,              ///< init check error.
    EBADARGS,           ///< bad arguments.
    ETIMEOUT,           ///< time out.
    ENONSUPPORT,        ///< not support.
    EUNKOWNERRNO,       ///< unknow error.

//file return val
    ESTATE,

    FILE_EACCES,
    FILE_EFAULT,
    FILE_EINVAL,
    FILE_EIO,
    FILE_ELOOP,
    FILE_ENAMETOOLONG,
    FILE_ENOENT,
    FILE_ENOMEM,
    FILE_ENOTDIR,

};

}

#endif
