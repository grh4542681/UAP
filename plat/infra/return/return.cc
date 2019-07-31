#include "return.h"

namespace ret {

std::map<const int, const std::string> Return::ECodeMap = {
     { ECode::UNKNOW, "Unknow error code." },
     { ECode::SUCCESS, "Success" },
     { ECode::ERROR, "Error." },

     { ECode::EBADARGS, "Bad arguments." }
};

}
