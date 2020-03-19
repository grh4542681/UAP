#include "mempool_return.h"

namespace mempool {

MempoolRet::ECodeMapType MempoolRet::ECodeMap = {
    // fifo return val
    { ECode::EALLOC, "" },
};

}
