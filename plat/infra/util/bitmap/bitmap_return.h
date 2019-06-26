#ifndef __BITMAP_RETURN_H__
#define __BITMAP_RETURN_H__

namespace util::bitmap {

enum class BitmapRet: int {
//common return val
    SUCCESS = 0,
    ERROR = -999,
    EMALLOC,
    EINIT,
    ETIMEOUT,
    EBADARGS,
    EUNKOWNERRNO,
    ESUBCLASS,
    ENSUPTYPE,

};

}

#endif
