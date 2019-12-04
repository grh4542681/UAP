#include "message_header.h"

namespace message {

MessageHeader::MessageHeader() {
    mid_ = MessageId::GenMessageIdByTime();
}
MessageHeader::~MessageHeader() {

}

MessageRet MessageHeader::SerializationJson(void* ptr, size_t* size)
{

}
MessageRet MessageHeader::DeserializationJson(void* ptr, size_t* size)
{

}

MessageRet MessageHeader::SerializationXml(void* ptr, size_t* size)
{

}
MessageRet MessageHeader::DeserializationXml(void* ptr, size_t* size)
{

}

MessageRet MessageHeader::SerializationProtobuf(void* ptr, size_t* size)
{

}
MessageRet MessageHeader::DeserializationProtobuf(void* ptr, size_t* size)
{

}

}
