#include "io_return.h"

namespace io {

IoRet::ECodeMapType IoRet::ECodeMap = {
     { ECode::IO_EFDTYPE, "Bad file descriptor type." },
     { ECode::IO_EUNKNOWEVENT, "Unknow select event." },
     { ECode::IO_EUNKNOWFD, "" },
     { ECode::IO_EMATCHEVENT, "" },
     { ECode::IO_EADDEVENT, "" },
     { ECode::IO_ENOCALLBACK, "" },

     { ECode::IO_EBADSELECTITEM, "" },
     { ECode::IO_ENOSELECTITEM, "" },

     { ECode::IO_EINPUTCB, "" },
     { ECode::IO_EOUTPUTCB, "" },
     { ECode::IO_EERRCB, "" }
};

}
