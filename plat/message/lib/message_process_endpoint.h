#ifndef __MESSAGE_PROCESS_ENDPOINT_H__
#define __MESSAGE_PROCESS_ENDPOINT_H__

#include "process_id.h"

#include "message_return.h"
#include "message_endpoint_type.h"
#include "message_endpoint_status.h"

namespace message {

class MessageProcessEndpoint {
public:
    MessageProcessEndpoint();
    ~MessageProcessEndpoint();

    MessageRet Send();
    MessageRet Recv();

private:
    char name_[128] = { 0 };

    MessageEndpointType scope_;
    MessageEndpointType type_;
    MessageEndpointStatus status_;
};

}

#endif
