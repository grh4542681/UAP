#ifndef __MESSAGE_ENDPOINT_ROLE_H__
#define __MESSAGE_ENDPOINT_ROLE_H__

namespace message {

enum class MessageEndpointRole {
    Internal,
    External,

    Management,
    MessageQue,
};

}

#endif
