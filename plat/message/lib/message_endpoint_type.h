#ifndef __MESSAGE_ENDPOINT_TYPE_H__
#define __MESSAGE_ENDPOINT_TYPE_H__

namespace message {

enum class MessageEndpointType {
    Public,
    Private,
    Local,
    Remote,

    Socket,
    Fifo,
};

}

#endif
