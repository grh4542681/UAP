#include "mempool_untrack.h"

namespace mempool {

MemPoolUntrack* MemPoolUntrack::getInstance()
{
    if (!pInstance) {
        pInstance = new MemPoolUntrack();
    }
    return pInstance;
}

};
