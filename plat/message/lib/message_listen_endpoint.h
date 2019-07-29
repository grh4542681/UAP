#ifndef __MESSAGE_LISTEN_ENDPOINT_H__
#define __MESSAGE_LISTEN_ENDPOINT_H__

#include "process_id.h"

#include "message_return.h"
#include "message_endpoint_type.h"
#include "message_endpoint_role.h"
#include "message_endpoint_status.h"
#include "message_endpoint.h"

namespace message {

class MessageListenEndpoint {
public:
    typedef struct _MessageListenEndpointInfo {
        char name_[128] = { 0 };
        process::ProcessID pid_;
        MessageEndpointRole role_;
        MessageEndpointType type_;
        MessageEndpointStatus status_;
    } MessageListenEndpointInfo;
public:
    MessageListenEndpoint();
    ~MessageListenEndpoint();

private:
    MessageListenEndpointInfo ep_info_;
    std::map<std::string, MessageEndpoint> tep_map_;
};

}

#endif
