#ifndef __MESSAGE_LISTENER_H__
#define __MESSAGE_LISTENER_H__

#include <map>

#include "mempool.h"
#include "timer_time.h"
#include "thread_id.h"
#include "sock_address.h"
#include "sock_server.h"
#include "io_select_item_template.h"

#include "message_return.h"
#include "message_log.h"
#include "message_defines.h"
#include "message_raw.h"
#include "message_remote.h"
#include "message_endpoint.h"

namespace message {
class MessageAgent;
class MessageListener : public MessageRaw {
public:
    //typedef io::IoRet (*Callback)(io::SelectItemTemplate<MessageListener>* item);
    typedef std::function<io::IoRet(MessageListener*,io::SelectItemTemplate<MessageListener>*, int)> Callback;
    friend class mempool::MemPool;
    friend class MessageAgent;
public:
    enum class Type : int {
        WorkerListener,
        KeeperListener,
        NormalListener,
    };

    enum class State : int {
        Initialize,
        Ready,
        Listening,
        Error,
    };

    typedef struct _Info {
        std::string name_;
        sock::SockAddress address_;

        int endpoint_num_;
        timer::Time create_time_;
        State state_;
    } Info;

public:
    ~MessageListener();

    std::string GetName();
    State& GetState();
    Callback& GetCallback();

    sock::SockServer& GetSockServer();

    bool IsReady();

    Callback callback_;
private:
    MessageAgent* agent_;
    Info info_;
    State state_;
    sock::SockServer server_;
    sock::SockFD sfd_;
    std::map<std::string, MessageEndpoint*> tep_map_;
    std::map<std::string, MessageRemote*> listen_remote_ep_map_;
    //io::IoRet (*callback_)(io::SelectItemTemplate<MessageListener>* item);
private:
    MessageListener(std::string name, const sock::SockAddress& addr, Callback callback = &MessageListener::_common_listener_callback);
    MessageListener(std::string name, const sock::SockFD& sfd, Callback callback = &MessageListener::_common_listener_callback);
    MessageListener(MessageListener& other);
    const MessageListener& operator=(const MessageListener& other);

    io::IoRet _common_listener_callback(io::SelectItemTemplate<MessageListener>* item, int events);
};


}

#endif
