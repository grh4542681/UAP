#ifndef __MESSAGE_SERVER_H__
#define __MESSAGE_SERVER_H__

#include "sock_server.h"

#include "message_log.h"
#include "message_return.h"
#include "message_topology.h"
#include "message_manager_server.h"

namespace message {

class MessageServer {
public:
    MessageServer();
    ~MessageServer();

    MessageRet Run();

    static MessageTopology Topology;
    static void Main(int i,std::string str);
private:
    MessageManagerServer manager_;
};

}

#endif
