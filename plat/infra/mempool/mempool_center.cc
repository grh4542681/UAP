#include <stdio.h>
#include "mempool_center.h"

namespace mempool {

MemPoolCenter* MemPoolCenter::pInstance = NULL;

MemPoolCenter::MemPoolCenter() {

}

MemPoolCenter::~MemPoolCenter() {

}

MemPoolCenter* MemPoolCenter::getInstance() {
    if (!pInstance) {
        pInstance = new MemPoolCenter();
    }
    return pInstance;
}

} //namespace end
