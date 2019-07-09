#ifndef __MESSAGE_TYPE_H__
#define __MESSAGE_TYPE_H__

#include "message_stream_binary.h"

namespace message {

enum class MessageType : int {
    Memory,
    FixedLen,
    KeyValue,
    Json,
    XML,
};

MessageStreamBinary& operator<<(MessageStreamBinary& bs, MessageType& mtype);
MessageStreamBinary& operator>>(MessageStreamBinary& bs, MessageType& mtype);

}

#endif
