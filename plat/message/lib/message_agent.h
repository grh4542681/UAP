#ifndef __MESSAGE_AGENT_H__
#define __MESSAGE_AGENT_H__

#include <map>

#include "vtime.h"
#include "process_id.h"
#include "process_info.h"
#include "thread_id.h"
#include "thread_template.h"
#include "sock_client.h"
#include "sock_address.h"
#include "io_select.h"

#include "message_api.h"
#include "message_defines.h"
#include "message_raw.h"
#include "message_endpoint.h"
#include "message_listener.h"
#include "message_agent_state.h"

namespace message {

class MessageAgent : MessageRaw {
public:
    typedef struct _MessageAgentInfo {
        std::string name_;
        process::ProcessID pid_;

        size_t listener_num_;
        timer::Time create_time_;
        MessageAgentState state_;
    } MessageAgentInfo;

public:
    MessageAgent();
    ~MessageAgent();

    std::string GetName();
    sock::SockClient& GetClient();

    MessageRet Register();
    MessageRet Unregister();

    MessageRet Serialization(MessageStreamBinary& bs);
    MessageRet Deserialization(MessageStreamBinary& bs);

    MessageRet RegisterEP(MessageEndpoint& ep);
    MessageRet RegisterEP(std::string name, MessageEndpoint& ep);
    MessageRet UnregisterEP(MessageEndpoint& ep);
    MessageRet UnregisterEP(std::string listener_name, std::string ep_name);

    MessageRet RegisterListenEP(MessageListener& lep);
    MessageRet UnregisterListenEP(std::string name);

    MessageListener* LookupLinstenEP();
    MessageListener* LookupLinstenEP(std::string listener_name);

    MessageEndpoint* LookupEP(std::string ep_name);
    MessageEndpoint* LookupEP(std::string listener_name, std::string ep_name);

    MessageRet Run();
public:
    static io::IoRet message_client_callback(io::SelectItem* item);
    static int message_listener_thread(MessageAgent* mg);
    static MessageAgent* getInstance();

private:
    bool init_flag_ = false;
    MessageAgentInfo info_;
    std::map<std::string, MessageListener*> listen_ep_map_;
    thread::ThreadTemplate<decltype(&message_listener_thread), int> listener_;
    sock::SockClient client_;
    io::Select select_;

    static MessageAgent* pInstance;
};

}

#endif
