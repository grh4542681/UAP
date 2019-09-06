#ifndef __MESSAGE_LISTENER_H__
#define __MESSAGE_LISTENER_H__

#include <map>

#include "vtime.h"
#include "thread_id.h"
#include "io_select_item.h"

#include "message_return.h"
#include "message_defines.h"
#include "message_raw.h"
#include "message_endpoint.h"
#include "message_listener_state.h"

namespace message {
class MessageAgent;
class MessageListener : public MessageRaw, public io::SelectItem {
public:
    typedef struct _MessageListenerInfo {
        std::string name_;
        std::string agent_name_;

        int endpoint_num_;
        timer::Time create_time_;
        MessageListenerState state_;
    } MessageListenerInfo;
public:
    MessageListener(std::string name, io::FD& fd);
    ~MessageListener();

    MessageRet Register();
    MessageRet Unregister();

private:
    MessageAgent* agent_;
    MessageListenerInfo info_;
    std::map<std::string, MessageEndpoint*> tep_map_;
};

}

#endif
