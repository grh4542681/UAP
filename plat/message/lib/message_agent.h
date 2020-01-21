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
#include "message_endpoint.h"
#include "message_listener.h"
#include "message_remote.h"
#include "message_local.h"
#include "message_manager.h"
//#include "message_heartbeat.h"

namespace message {

class MessageAgent {
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

    bool IsReady();
    State& GetState();
    Type& GetType();
    MessageAgent& SetType(const Type&);

    bool HasManager();
    MessageManager* GetManager();

    MessageListener* GetLinstener(std::string l_name);
    MessageEndpoint* GetEndpoint(std::string listener_name, std::string ep_name);

    template < typename ... Args > MessageRet RegisterManager(Args&& ... args) {
        if (manager_ && manager_->IsAvailable()) {
            return MessageRet::MESSAGE_MANAGER_EEXIST;
        }
        manager_ = manager_ ? mempool_->Reset<MessageManager>(manager_, std::forward<Args>(args)...)
                        : mempool_->Malloc<MessageManager>(std::forward<Args>(args)...);
        if (!manager_) {
            return MessageRet::EMALLOC;
        }
        if (!manager_->IsAvailable()) {
            return MessageRet::MESSAGE_AGENT_ECONN;
        }
        io::SelectItemTemplate<MessageManager> manager_selectitem(manager_, manager_->GetManagerFD(), manager_->ReceiveMessageProcess);
        manager_selectitem.GetSelectEvent().SetEvent(io::SelectEvent::Input);
        manager_->Write("hello world", 11);
        select_.AddSelectItem<io::SelectItemTemplate<MessageManager>>(manager_selectitem);
        return MessageRet::SUCCESS;
    }

    template < typename ... Args > MessageRet RegisterListener(std::string name, Args&& ... args) {
        if (LookupLinstener(name)) {
            return MessageRet::MESSAGE_LISTENER_EREPEAT;
        }
        MessageListener* listener = mempool_->Malloc<MessageListener>(name, std::forward<Args>(args)...);
        if (!listener) {
            return MessageRet::EMALLOC;
        }
        if (!(listener->IsReady())) {
            mempool_->Free<MessageListener>(listener);
            return MessageRet::MESSAGE_LISTENER_ESTATE;
        }
        io::SelectItemTemplate<MessageListener> listener_selectitem(listener, listener->GetSockServer().GetSockFD(), listener->GetCallback());
        listener_selectitem.GetSelectEvent().SetEvent(io::SelectEvent::Input);
        select_.AddSelectItem<io::SelectItemTemplate<MessageListener>>(listener_selectitem);
        listener_map_.insert({name, listener});
        return MessageRet::SUCCESS;
    }
    MessageRet UnregisterListener(std::string name);

    template < typename ... Args > MessageRet RegisterEndpoint(std::string l_name, Args&& ... args) {
        return MessageRet::SUCCESS;
    }
    MessageRet UnregisterEP(std::string l_name, std::string e_name);

    MessageListener* LookupLinstener(std::string l_name);
    MessageIO LookupEndpoint(std::string listener_name, std::string ep_name);

    MessageRet Run();
public:
    static std::string DefaultName;
    static MessageAgent* getInstance();

private:
    MessageRet _register_agent_to_manager(MessageAgent& agent);
    MessageRet _register_listener_to_manager(MessageListener& listener);
    MessageRet _register_endpoint_to_manager(MessageEndpoint& endpoint);
private:
    mempool::MemPool* mempool_;
    Type type_;
    Info info_;
//    HeartbeatServer heartbeat_s_;
//    HeartbeatClient heartbeat_c_;

    MessageManager* manager_ = NULL;
    std::map<std::string, MessageListener*> listener_map_;
    std::map<std::string, MessageRemote*> listen_remote_ep_map_;
    std::map<std::string, MessageLocal*> listen_local_ep_map_;

    io::AutoSelect select_;

    static MessageAgent* pInstance;

};

}

#endif
