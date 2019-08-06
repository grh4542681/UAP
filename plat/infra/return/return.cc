#include "return.h"

namespace ret {

Return::ECodeMapType Return::ECodeMap = {
    { ECode::UNKNOW, "Unknow error code." },
    { ECode::ERROR, "Error." },

    { ECode::EBADARGS, "Bad arguments." },
    { ECode::EMALLOC, "Malloc error." },
    { ECode::EINIT, "Inilazition error." },
    { ECode::ETIMEOUT, "Time out." },
    { ECode::ESUBCLASS, "Can not find subclass." },
    { ECode::ECONSTRUCT, "Construct function error." }
};

}
