#ifndef __MESSAGE_ENDPOINT_TYPE_H__
#define __MESSAGE_ENDPOINT_TYPE_H__

namespace message {

enum class MessageEndpointType {
    Socket,
    Fifo,
    Event,
    Timer,

    MsgShm,
};

}

#endif
