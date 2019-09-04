#ifndef __MESSAGE_LISTENER_H__
#define __MESSAGE_LISTENER_H__

#include <map>

#include "thread_id.h"

#include "message_return.h"
#include "message_defines.h"
#include "message_raw.h"
#include "message_endpoint.h"

namespace message {
class MessageAgent;
class MessageListener : MessageRaw {
public:
    typedef struct _MessageListenerInfo {
        char name_[MESSAGE_ENDPOINT_NAME_MAX_LEN] = { 0 };
        char agent_name_[MESSAGE_ENDPOINT_NAME_MAX_LEN] = { 0 };
        thread::ThreadID tid_;
    } MessageListenerInfo;
public:
    MessageListener(std::string name, io::FD& fd) {
        if (name.size() > MESSAGE_ENDPOINT_NAME_MAX_LEN) {
            return;
        }
    }
    ~MessageListener();

    MessageRet Register();
    MessageRet Unregister();

private:
    MessageAgent* agent_;
    MessageListenerInfo ep_info_;
    std::map<std::string, MessageEndpoint*> tep_map_;
};

}

#endif
