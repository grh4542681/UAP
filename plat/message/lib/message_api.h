#ifndef __MESSAGE_API_H__
#define __MESSAGE_API_H__

#include "mempool.h"
#include "sock_address.h"

namespace message {

sock::SockAddress* GetMessageServerAddress();

}

#endif
