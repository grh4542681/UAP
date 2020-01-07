#ifndef __MESSAGE_HEARTBEAT_H__
#define __MESSAGE_HEARTBEAT_H__

#include "thread_template.h"

#include "message_return.h"
#include "message_uri.h"
#include "message_remote.h"
#include "message_internal.h"

namespace message {

class MessageHeartbeat {
public:
    class Element {
    public:
        using ExceptCallbackFunc = std::function<void(MessageHeartbeat::Element&)>;
        using TriggerCallbackFunc = std::function<void(MessageHeartbeat::Element&)>;
    public:
        MessageURI uri;
        timer::Time rate;
        MessageRemote remote;
        ExceptCallbackFunc except_callback;
        TriggerCallbackFunc trigger_callback;
    };

public:
    MessageHeartbeat();
    ~MessageHeartbeat();

    MessageRet Add(MessageHeartbeat::Element& element);
    MessageRet Del(MessageURI uri);
private:
    static MessageRet _select_listener_thread_handler(MessageHeartbeat* instance);
    thread::ThreadTemplate<decltype(&_select_listener_thread_handler), MessageRet> listener_thread_;
};

}

#endif
