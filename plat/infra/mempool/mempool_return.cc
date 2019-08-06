#include "mempool_return.h"

namespace mempool {

MemPoolRet::ECodeMapType MemPoolRet::ECodeMap = {
    // fifo return val
    { ECode::EALLOC, "" },
};

}
