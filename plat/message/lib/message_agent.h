#ifndef __MESSAGE_AGENT_H__
#define __MESSAGE_AGENT_H__

#include "io_fd.h"
#include "message_process_endpoint.h"
#include "message_handle.h"

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

    MessageRet AddHandle(std::string name, io::FD& fd);
    MessageRet DelHandle(std::string name);
    MessageHandle GetHandle(std::string name);

    void Run();

private:
    void _run();

    MessageProcessEndpoint pep_;
    std::map<std::string, MessageEndpoint> tep_map_;

};

}

#endif
