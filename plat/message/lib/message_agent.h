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

namespace message {

class MessageAgent : MessageRaw {
public:
    enum class Type : int {
        WorkerAgent,
        KeeperAgent,
        NormalAgent,
    };

    enum class State {
        Initialize,
        Listenning,
        Ready,
        Disable,
        Error,
    };

    typedef struct _Info {
        size_t listener_num_;
        timer::Time create_time_;
        State state_;
    } Info;

public:
    MessageAgent();
    ~MessageAgent();

    //from MessageRaw
    MessageRet Serialization(MessageStreamBinary& bs);
    MessageRet Deserialization(MessageStreamBinary& bs);

    bool IsReady();
    State& GetState();
    Type& GetType();
    MessageAgent& SetType(const Type&);

    bool HasManager();
    MessageRemote* GetManager();

    MessageListener* GetLinstener(std::string l_name);
    MessageEndpoint* GetEndpoint(std::string listener_name, std::string ep_name);

    MessageRet RegisterAgent();
    MessageRet UnregisterAgent();

    MessageRet RegisterListener(std::string name, const sock::SockAddress& addr);
    MessageRet UnregisterListener(std::string name);

    template < typename ... Args > MessageRet RegisterEndpoint(std::string l_name, Args&& ... args);
    MessageRet UnregisterEP(std::string l_name, std::string e_name);

    MessageListener* LookupLinstener(std::string l_name);
    MessageListener* LookupEndpoint(std::string listener_name, std::string ep_name);
    MessageRet SendManager();

    MessageRet Run();
public:
    static std::string DefaultName;
    static MessageAgent* getInstance();

private:
    mempool::MemPool* mempool_;
    Type type_;
    Info info_;

    MessageRemote* remote_manager_ = NULL;
    std::map<std::string, MessageListener*> listen_local_ep_map_;
    std::map<std::string, MessageRemote*> listen_remote_ep_map_;

    io::AutoSelect select_;

    static MessageAgent* pInstance;

};

}

#endif
