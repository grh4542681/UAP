#ifndef __MESSAGE_AGENT_H__
#define __MESSAGE_AGENT_H__

#include <map>

#include "mempool.h"
#include "timer_time.h"
#include "thread_template.h"
#include "sock_client.h"
#include "io_auto_select.h"

#include "message_api.h"
#include "message_defines.h"
#include "message_raw.h"
#include "message_endpoint.h"
#include "message_listener.h"
#include "message_remote.h"
#include "message_agent_state.h"
#include "message_link.h"

namespace message {

class MessageAgent : MessageRaw {
public:
    typedef struct _MessageAgentInfo {
        size_t listener_num_;
        timer::Time create_time_;
        MessageAgentState state_;
    } MessageAgentInfo;

public:
    MessageAgent();
    ~MessageAgent();

    //from MessageRaw
    MessageRet Serialization(MessageStreamBinary& bs);
    MessageRet Deserialization(MessageStreamBinary& bs);

    MessageRemote* GetRemote();

    MessageListener* GetLinstener(std::string l_name);
    MessageEndpoint* GetEndpoint(std::string listener_name, std::string ep_name);

    MessageRet RegisterAgent();
    MessageRet UnregisterAgent();

    template < typename ... Args > MessageRet RegisterListener(Args&& ... args);
    MessageRet UnregisterListener(std::string name);

    template < typename ... Args > MessageRet RegisterEndpoint(std::string l_name, Args&& ... args);
    MessageRet UnregisterEP(std::string l_name, std::string e_name);

    MessageLink LookupLinstener(std::string l_name);
    MessageLink LookupEndpoint(std::string listener_name, std::string ep_name);

    MessageRet Run();
public:
    static MessageRet message_client_callback(MessageRemote::SelectItem* item);
    static MessageAgent* getInstance();

private:
    bool init_flag_ = false;
    mempool::MemPool* mempool_;
    MessageAgentInfo info_;

    MessageRemote* agent_client_;
    std::map<std::string, MessageListener*> listen_local_ep_map_;
    std::map<std::string, MessageRemote*> listen_remote_ep_map_;

    io::AutoSelect select_;

    static MessageAgent* pInstance;
};

}

#endif
