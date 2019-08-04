#include "return.h"

namespace ret {

Return::ECodeMapType Return::ECodeMap = {
     { ECode::UNKNOW, "Unknow error code." },
     { ECode::SUCCESS, "Success" },
     { ECode::ERROR, "Error." },

     { ECode::EBADARGS, "Bad arguments." }
};

}
