#include "io_return.h"

namespace io {

IoRet::ECodeMapType IoRet::ECodeMap = {
     { ECode::EFDTYPE, "Bad file descriptor type." }
};

}