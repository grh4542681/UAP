#ifndef __MESSAGE_RAW_H__
#define __MESSAGE_RAW_H__

#include "message_return.h"

namespace message {

enum class MessageProto {
    Json,
    Xml,
    Protobuf,
};

class MessageRaw {
public:
    MessageRaw() {}
    virtual ~MessageRaw() { }

    MessageRet Serialization(MessageProto&) { return MessageRet::ESUBCLASS; }
    MessageRet Deserialization(MessageProto&, void* data, size_t size) { return MessageRet::ESUBCLASS; }

    virtual MessageRet SerializationJson(void* ptr, size_t* size) { return MessageRet::ESUBCLASS; }
    virtual MessageRet DeserializationJson(void* ptr, size_t* size) { return MessageRet::ESUBCLASS; }

    virtual MessageRet SerializationXml(void* ptr, size_t* size) { return MessageRet::ESUBCLASS; }
    virtual MessageRet DeserializationXml(void* ptr, size_t* size) { return MessageRet::ESUBCLASS; }

    virtual MessageRet SerializationTvl(void* ptr, size_t* size) { return MessageRet::ESUBCLASS; }
    virtual MessageRet DeserializationTvl(void* ptr, size_t* size) { return MessageRet::ESUBCLASS; }
};

}

#endif
