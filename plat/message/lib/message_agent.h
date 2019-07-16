#ifndef __MESSAGE_AGENT_H__
#define __MESSAGE_AGENT_H__

#include <map>

#include "io_fd.h"
#include "message_endpoint.h"
#include "message_agent_endpoint.h"
#include "message_handle.h"

namespace message {

class MessageAgent {
public:
    MessageAgent();
    ~MessageAgent();

    MessageRet RegisterAgent();
    MessageRet UnregisterAgent();

    MessageRet RegisterEP(std::string, MessageEndpoint& ep);
    MessageRet UnregisterEP(std::string, MessageEndpoint& ep);

    MessageRet AddAgentEP(std::string name, io::FD& fd);
    MessageRet DelAgentEP(std::string name);

    void Run();

private:
    void _run();

    std::map<std::string, MessageAgentEndpoint> agent_ep_map_;

};

}

#endif
