#ifndef __MESSAGE_AGENT_H__
#define __MESSAGE_AGENT_H__

#include <map>

#include "vtime.h"
#include "process_id.h"
#include "thread_id.h"
#include "thread_template.h"
#include "sock_client.h"
#include "sock_address.h"

#include "message_defines.h"
#include "message_endpoint.h"
#include "message_listen_endpoint.h"
#include "message_agent_state.h"

namespace message {

class MessageAgent {
public:
    typedef struct _MessageAgentInfo {
        char name_[MESSAGE_ENDPOINT_NAME_MAX_LEN] = { 0 };
        process::ProcessID pid_;
        thread::ThreadID tid_;

        size_t listen_ep_num_;
        timer::Time create_time_;
        MessageAgentState state_;
    } MessageAgentInfo;

public:
    MessageAgent(std::string name);
    ~MessageAgent();

    MessageRet RegisterEP(MessageEndpoint& ep);
    MessageRet RegisterEP(std::string name, MessageEndpoint& ep);
    MessageRet UnregisterEP(MessageEndpoint& ep);
    MessageRet UnregisterEP(std::string listener_name, std::string ep_name);

    MessageRet RegisterListenEP(MessageListenEndpoint& lep);
    MessageRet UnregisterListenEP(std::string name);

    MessageListenEndpoint* LookupLinstenEP();
    MessageListenEndpoint* LookupLinstenEP(std::string listener_name);

    MessageEndpoint* LookupEP(std::string ep_name);
    MessageEndpoint* LookupEP(std::string listener_name, std::string ep_name);

    void Run();
public:
    static int message_listener_thread(MessageAgent* mg);
    static sock::SockAddress* GetMessageServerAddress();
private:
    bool init_flag_ = false;
    MessageAgentInfo info_;
    std::map<std::string, MessageListenEndpoint*> listen_ep_map_;
    sock::SockClient client_;

    static sock::SockAddress* MessageServerAddress;
};

}

#endif
