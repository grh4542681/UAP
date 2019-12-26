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

class MessageAgent : public MessageRaw {
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
    MessageRet Serialization(void* ptr, size_t* size);
    MessageRet Deserialization(void* ptr, size_t* size);

    bool IsReady();
    State& GetState();
    Type& GetType();
    MessageAgent& SetType(const Type&);

    bool HasManager();
    MessageRemote* GetManager();
    MessageRet SetManager(MessageRemote*);

    MessageListener* GetLinstener(std::string l_name);
    MessageEndpoint* GetEndpoint(std::string listener_name, std::string ep_name);

    MessageRet RegisterAgent();
    MessageRet UnregisterAgent();

    template < typename ... Args > MessageRet RegisterManager(Args&& ... args) {
        if (remote_manager_) {
            return MessageRet::MESSAGE_MANAGER_EEXIST;
        }
        remote_manager_ = mempool_->Malloc<MessageRemote>("LOCAL", "MSG_CTRL", "MSG_CTRL", std::forward<Args>(args)...);
        if (!remote_manager_) {
            return MessageRet::EMALLOC;
        }
        if (!remote_manager_->IsReady()) {
            return MessageRet::MESSAGE_AGENT_ECONN;
        }
        io::SelectItemTemplate<MessageRemote> manager_selectitem(remote_manager_, remote_manager_->GetRemoteFD());
        manager_selectitem.GetSelectEvent().SetEvent(io::SelectEvent::Input);
        manager_selectitem.InputFunc = remote_manager_->GetCallback();
        remote_manager_->GetRemoteFD().Write("hello world", 12);
        select_.AddSelectItem<io::SelectItemTemplate<MessageRemote>>(manager_selectitem);
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
        io::SelectItemTemplate<MessageListener> listener_selectitem(listener, listener->GetSockServer().GetSockFD());
        listener_selectitem.GetSelectEvent().SetEvent(io::SelectEvent::Input);
        listener_selectitem.InputFunc = listener->GetCallback();
        select_.AddSelectItem<io::SelectItemTemplate<MessageListener>>(listener_selectitem);
        listen_local_ep_map_.insert({name, listener});
        return MessageRet::SUCCESS;
    }
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

    io::AutoSelect select_;

    static MessageAgent* pInstance;

};

}

#endif
