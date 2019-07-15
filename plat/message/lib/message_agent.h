#ifndef __MESSAGE_AGENT_H__
#define __MESSAGE_AGENT_H__

#include "message_process_endpoint.h"

namespace message {

class MessageAgent {
public:
    typedef struct _MessageAgentConfig {
        size_t cache_size;
    }MessageAgentConfig;

public:
    MessageAgent(MessageAgentConfig& config, MessageProcessEndpoint& pep);
    ~MessageAgent();

    MessageRet RegisterAgent();
    MessageRet UnregisterAgent();

    MessageRet RegisterEP(MessageEndpoint& ep);
    MessageRet UnregisterEP(MessageEndpoint& ep);

    MessageRet AddFD();
    MessageRet DelFD();

    void Run();

private:
    void _run();

    MessageProcessEndpoint pep_;
    std::map<std::string, MessageEndpoint> tep_map_;

};

}

#endif
