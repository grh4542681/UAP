#include "message_api.h"

namespace message {

static sock::SockAddress* MessageServerAddress = NULL;
sock::SockAddress* GetMessageServerAddress()
{
    if (!MessageServerAddress) {
        MessageServerAddress = mempool::MemPool::getInstance()->Malloc<sock::SockAddress>(sock::SockFamily::TCP_LOCAL, "/home/ezgaoro/workspace/cppfram/tmp/messaged.sock");
    }
    return MessageServerAddress;
}

}
