#include "mempool.h"

#include "message_log"
#include "message_return.h"
#include "message_ctrl.h"

namespace message {

MessageCtrl* MessageCtrl::pInstance = NULL;

MessageCtrl::MessageCtrl()
{

}

MessageCtrl::~MessageCtrl()
{

}

MessageCtrl* MessageCtrl::getInstance()
{
    if (!pInstance) {
        pInstance = mempool::MemPool::getInstance()->Malloc<MessageCtrl>();
    }
    return pInstance;
}

}
