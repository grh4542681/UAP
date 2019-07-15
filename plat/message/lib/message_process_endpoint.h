#ifndef __MESSAGE_PROCESS_ENDPOINT_H__
#define __MESSAGE_PROCESS_ENDPOINT_H__

#include "process_id.h"

#include "message_return.h"
#include "message_thread_endpoint.h"

namespace message {

class MessageProcessEndpoint {
public:
    MessageProcessEndpoint();
    ~MessageProcessEndpoint();

    MessageRet Send();
    MessageRet Recv();

private:
    char name_[128] = { 0 };
    util::ip::Ipv4 ip4_;
    util::ip::Ipv6 ip6_;
    util::ip::Mac mac_;

    MessageEndpointType scope_;
    MessageEndpointType type_;
    MessageEndpointStatus status_;
};

}

#endif
