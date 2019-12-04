#include "message_id.h"

namespace message {

MessageId::MessageId() {
    id_ = 0;
}

MessageId::MessageId(MessageId& other) {
    id_ = other.id_;
}

MessageId::~MessageId() { }

MessageId& MessageId::operator=(const MessageId& other) {
    id_ = other.id_;
    return *this;
}

long MessageId::GetId() {
    return id_;
}

MessageId MessageId::GenMessageIdByTime() {
   return MessageId((long)time(NULL));
}

MessageRet MessageId::SerializationJson(std::string* str) {
    return MessageRet::ESUBCLASS;
}

MessageRet MessageId::DeserializationJson(std::string* str) {
    return MessageRet::ESUBCLASS;
}

MessageRet MessageId::SerializationXml(void* ptr, size_t* size) {
    return MessageRet::ESUBCLASS;
}

MessageRet MessageId::DeserializationXml(void* ptr, size_t* size) {
    return MessageRet::ESUBCLASS;
}

MessageRet MessageId::SerializationTvl(void* ptr, size_t* size) {
    return MessageRet::ESUBCLASS;
}

MessageRet MessageId::DeserializationTvl(void* ptr, size_t* size) {
    return MessageRet::ESUBCLASS;
}

}
