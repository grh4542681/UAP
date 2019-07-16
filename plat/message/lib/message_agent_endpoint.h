#ifndef __MESSAGE_PROCESS_ENDPOINT_H__
#define __MESSAGE_PROCESS_ENDPOINT_H__

#include "process_id.h"

#include "message_return.h"
#include "message_endpoint_type.h"
#include "message_endpoint_status.h"

namespace message {

class MessageAgentEndpoint {
public:
    typedef struct _MessageAgentEndpointInfo {
        char name_[128] = { 0 };
        MessageEndpointType scope_;
        MessageEndpointType type_;
        MessageEndpointStatus status_;
    } MessageAgentEndpointInfo;
public:
    MessageAgentEndpoint();
    ~MessageAgentEndpoint();

private:
    MessageAgentEndpointInfo ep_info_;
    std::map<std::string, MessageEndpoint> tep_map_;
};

}

#endif
