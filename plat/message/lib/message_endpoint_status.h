#ifndef __MESSAGE_ENDPOINT_STATUS_H__
#define __MESSAGE_ENDPOINT_STATUS_H__

namespace message {

enum class MessageEndpointStatus : int {
    Unknow = 0,
    Ready,
    Listen,
    Close,
};

};

#endif
