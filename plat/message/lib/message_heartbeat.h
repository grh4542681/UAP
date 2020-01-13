#ifndef __MESSAGE_HEARTBEAT_H__
#define __MESSAGE_HEARTBEAT_H__

#include "io_auto_select.h"
#include "thread_template.h"
#include "fsm.h"

#include "message_return.h"
#include "message_uri.h"
#include "message_remote.h"
#include "message_internal.h"

namespace message {

class MessageHeartbeatElement {
public:
    using ExceptCallbackFunc = std::function<void(MessageHeartbeatElement&)>;
    using TriggerCallbackFunc = std::function<void(MessageHeartbeatElement&)>;
public:
    MessageURI uri_;
    timer::Time rate_;
    ExceptCallbackFunc except_callback_;
    TriggerCallbackFunc trigger_callback_;

    timer::Time last_time_;
};

class MessageHeartbeatClient {
public:
    MessageHeartbeatClient();
    ~MessageHeartbeatClient();

    MessageRet Add(MessageHeartbeatElement& element);
    MessageRet Del(MessageURI uri);
private:
private:
    io::AutoSelect select_;
};

class MessageHeartbeatServer {

};

}

#endif
