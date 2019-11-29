#ifndef __MESSAGE_RAW_H__
#define __MESSAGE_RAW_H__

#include "message_return.h"

namespace message {

class enum MessageProto {
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

    virtual MessageRet SerializationProtobuf(void* ptr, size_t* size) { return MessageRet::ESUBCLASS; }
    virtual MessageRet DeserializationProtobuf(void* ptr, size_t* size) { return MessageRet::ESUBCLASS; }

private:
    void* p_json_;
    void* p_xml_;
    void* p_protobuf_;
};

}

#endif
