#include "stddef.h"
#include "process_signal_ctrl.h"

namespace process::signal {

ProcessSignalCtrl* ProcessSignalCtrl::pInstance = NULL;

ProcessSignalCtrl::ProcessSignalCtrl()
{
    mempool_ = mempool::MemPool::getInstance();
}

ProcessSignalCtrl::~ProcessSignalCtrl()
{

}

ProcessSignalCtrl* ProcessSignalCtrl::getInstance()
{
    if (!pInstance) {
        pInstance = new ProcessSignalCtrl();
    }
    return pInstance;
}

}
