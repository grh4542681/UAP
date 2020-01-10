#ifndef __MESSAGE_HEARTBEAT_H__
#define __MESSAGE_HEARTBEAT_H__

#include "thread_template.h"

#include "message_return.h"
#include "message_uri.h"
#include "message_remote.h"
#include "message_internal.h"

namespace message {

class MessageHeartbeatClient {
public:
    class Element {
    public:
        using ExceptCallbackFunc = std::function<void(MessageHeartbeat::Element&)>;
        using TriggerCallbackFunc = std::function<void(MessageHeartbeat::Element&)>;
    public:
        MessageURI uri;
        timer::Time rate;
        ExceptCallbackFunc except_callback;
        TriggerCallbackFunc trigger_callback;
    };

//io::SelectItemTemplate<MessageListener> listener_selectitem(listener, listener->GetSockServer().GetSockFD(), listener->GetCallback());
public:
    MessageHeartbeat();
    ~MessageHeartbeat();

    MessageRet Add(MessageHeartbeat::Element& element);
    MessageRet Del(MessageURI uri);
private:
private:
    io::AutoSelect select_;
};

class MessageHeartbeatServer {

};

}

#endif
