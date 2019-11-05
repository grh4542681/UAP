#ifndef __MESSAGE_LISTENER_H__
#define __MESSAGE_LISTENER_H__

#include <map>

#include "timer_time.h"
#include "thread_id.h"
#include "sock_address.h"
#include "sock_server.h"
#include "io_select_item.h"

#include "message_return.h"
#include "message_log.h"
#include "message_defines.h"
#include "message_raw.h"
#include "message_endpoint.h"

namespace message {
class MessageAgent;
class MessageListener : public MessageRaw {
public:
    friend class MessageAgent;
public:
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
    MessageListener(std::string name, const sock::SockAddress& addr);
    ~MessageListener();

    State& GetState();
    sock::SockServer& GetSockServer();

    bool IsReady();

private:
    MessageAgent* agent_;
    Info info_;
    State state_;
    sock::SockServer server_;
    std::map<std::string, MessageEndpoint*> tep_map_;
private:
    MessageListener(MessageListener& other);
    const MessageListener& operator=(const MessageListener& other);
};

}

#endif
