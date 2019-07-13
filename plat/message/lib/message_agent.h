#ifndef __MESSAGE_AGENT_H__
#define __MESSAGE_AGENT_H__

namespace message {

class MessageAgent {
public:
    typedef struct _MessageAgentConfig {
        size_t cache_size;
    }MessageAgentConfig;

public:
    MessageAgent(MessageAgentConfig& config);
    ~MessageAgent();

    MessageRet AddItem();
    MessageRet DelItem();

private:
    void _message_listen_handler();
    void _fd_listen_handler();

};

}

#endif
