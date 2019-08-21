#include "io_return.h"

namespace io {

IoRet::ECodeMapType IoRet::ECodeMap = {
     { ECode::IO_EFDTYPE, "Bad file descriptor type." },
     { ECode::IO_EUNKNOWEVENT, "Unknow select event." }
};

}
