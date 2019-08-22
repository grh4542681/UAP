#ifndef __MESSAGE_SERVER_H__
#define __MESSAGE_SERVER_H__

#include "sock_server.h"

#include "message_log.h"
#include "message_api.h"
#include "message_return.h"

namespace message {

class MessageServer {
public:
    MessageServer();
    ~MessageServer();

    MessageRet Run();
private:
    sock::SockServer server_;
};

}

#endif
