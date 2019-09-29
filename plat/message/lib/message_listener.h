#ifndef __MESSAGE_LISTENER_H__
#define __MESSAGE_LISTENER_H__

#include <map>

#include "timer_time.h"
#include "thread_id.h"
#include "sock_fd.h"
#include "io_select_item.h"

#include "message_return.h"
#include "message_defines.h"
#include "message_raw.h"
#include "message_endpoint.h"
#include "message_listener_state.h"
#include "message_listener_select_item.h"

namespace message {
class MessageAgent;
class MessageListener : public MessageRaw {
public:
    typedef struct _MessageListenerInfo {
        std::string name_;
        sock::SockAddress address_;

        int endpoint_num_;
        timer::Time create_time_;
        MessageListenerState state_;
    } MessageListenerInfo;
public:
    MessageListener(std::string name, sock::SockAddress& addr);
    ~MessageListener();

    MessageListenerSelectItem& GetSelectItem();

    MessageRet Register();
    MessageRet Unregister();

private:
    bool init_flag_ = false;
    MessageAgent* agent_;
    MessageListenerInfo info_;
    sock::SockServer server_;
    MessageListenerSelectItem select_item_;
    std::map<std::string, MessageEndpoint*> tep_map_;
};

}

#endif
