#ifndef __MESSAGE_LISTEN_ENDPOINT_H__
#define __MESSAGE_LISTEN_ENDPOINT_H__

#include <map>

#include "thread_id.h"

#include "message_return.h"
#include "message_defines.h"
#include "message_endpoint_type.h"
#include "message_endpoint_role.h"
#include "message_endpoint_status.h"
#include "message_endpoint.h"

namespace message {
class MessageAgent;
class MessageListenEndpoint {
public:
    typedef struct _MessageListenEndpointInfo {
        char name_[MESSAGE_ENDPOINT_NAME_MAX_LEN] = { 0 };
        thread::ThreadID tid_;
        MessageEndpointRole role_;
        MessageEndpointType type_;
        MessageEndpointStatus status_;
    } MessageListenEndpointInfo;
public:
    MessageListenEndpoint(std::string name, io::FD& fd) {
        if (name.size() > MESSAGE_ENDPOINT_NAME_MAX_LEN) {
            return;
        }
    }
    ~MessageListenEndpoint();

private:
    MessageAgent* agent_;
    MessageListenEndpointInfo ep_info_;
    std::map<std::string, MessageEndpoint*> tep_map_;
};

}

#endif
