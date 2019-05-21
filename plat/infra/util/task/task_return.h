#ifndef __TASK_RETURN_H__
#define __TASK_RETURN_H__

namespace util::task {

enum class TaskRet: int {
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
