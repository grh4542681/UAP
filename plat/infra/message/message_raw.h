#ifndef __MESSAGE_RAW_H__
#define __MESSAGE_RAW_H__

#include <sstream>

#include "message_return.h"
#include "message_stream_binary.h"

namespace message {

class MessageRaw {
public:
    MessageRaw() { msg_len_ = 0; }
    virtual ~MessageRaw() { }

    virtual MessageRet Serialization(MessageStreamBinary&& bs) { return MessageRet::ESUBCLASS; }
    virtual MessageRet Deserialization(MessageStreamBinary&& bs) { return MessageRet::ESUBCLASS; }
public:
    unsigned int msg_len_;
};

}

#endif
