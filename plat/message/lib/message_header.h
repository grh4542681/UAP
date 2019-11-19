#ifndef __MESSAGE_HEADER_H__
#define __MESSAGE_HEADER_H__

#include "message_return.h"

#include "message_raw.h"
#include "message_id.h"
#include "message_type.h"

namespace message {

class MessageHeader : public MessageRaw {
public:
    MessageHeader(MessageType type) {
        mid_ = MessageId::GenMessageIdByTime();
        type_ = type;
    }
    ~MessageHeader() {

    }

    std::string Serialization();
    MesageRet Deserialization(std::string msg);
    
private:
    MessageId mid_;
    MessageType type_;
};

}

#endif
