#ifndef __MESSAGE_HEADER_H__
#define __MESSAGE_HEADER_H__

#include "message_return.h"

#include "message_raw.h"
#include "message_id.h"
#include "message_appid.h"

namespace message {

class MessageHeader : public MessageRaw {
public:
    MessageHeader();
    ~MessageHeader();

    MessageRet SerializationJson(void* ptr, size_t* size);
    MessageRet DeserializationJson(void* ptr, size_t* size);

    MessageRet SerializationXml(void* ptr, size_t* size);
    MessageRet DeserializationXml(void* ptr, size_t* size);

    MessageRet SerializationProtobuf(void* ptr, size_t* size);
    MessageRet DeserializationProtobuf(void* ptr, size_t* size);
    
private:
    MessageId mid_;
    MessageAppid appid_;
    uint32_t body_len_;
};

}

#endif
