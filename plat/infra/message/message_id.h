#ifndef __MESSAGE_ID_H__
#define __MESSAGE_ID_H__

#include "message_raw.h"

namespace message {

class MessageId : MessageRaw {
public:
    MessageId();
    MessageId(MessageId& other);
    ~MessageId();

    std::string toString();
    static MessageID GenMessageID();
    
    MessageRet Serialization(MessageStreamBinary&& bs);
    MessageRet Deserialization(MessageStreamBinary&& bs)
};

}

#endif
