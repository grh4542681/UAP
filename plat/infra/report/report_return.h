#ifndef __REPORT_RETURN_H__
#define __REPORT_RETURN_H__

namespace report {

enum class ReportRet: int {
//common return val
    SUCCESS = 0,
    ERROR = -999,
    EMALLOC,
    EINIT,
    ETIMEOUT,
    EBADARGS,

    EUNKOWNERRNO,
};

} // namespace mempool

#endif
