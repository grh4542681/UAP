#ifndef __MESSAGE_AGENT_H__
#define __MESSAGE_AGENT_H__

#include <map>

#include "io_fd.h"
#include "message_endpoint.h"
#include "message_agent_endpoint.h"
#include "message_listen_endpoint.h"
#include "message_handle.h"

namespace message {

class MessageAgent {
public:
    MessageAgent(std::string name);
    ~MessageAgent();

    MessageRet RegisterEP(std::string, MessageEndpoint& ep);
    MessageRet UnregisterEP(std::string, MessageEndpoint& ep);

    MessageRet RegisterListenEP(std::string name, io::FD& fd);
    MessageRet UnregisterListenEP(std::string name);

    void Run();

private:
    MessageAgentEndpoint aep_;
    std::map<std::string, MessageListenEndpoint> listen_ep_map_;

    void _run();
    MessageRet _register();
    SockAddress _get_message_deamon_address();
};

}

#endif
