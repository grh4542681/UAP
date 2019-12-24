#include <time.h>

#include "message_head.h"

namespace message {

MessageHead::MessageHead() {
    name_ = "head";
    mid_ = GenMessageIdByTime();
}
MessageHead::~MessageHead() {

}

long& MessageHead::GetMessageId()
{
    return mid_;
}

MessageAppid& MessageHead::GetMessageAppid()
{
    return appid_;
}

MessageFormat& MessageHead::GetMessageBodyFormat()
{
    return body_format_;
}

uint32_t MessageHead::GetMessageBodyLen()
{
    return body_len_;
}

MessageHead& MessageHead::SetMessageAppid(const MessageAppid& appid)
{
    appid_ = appid;
    return *this;
}

MessageHead& MessageHead::SetMessageBodyFormat(const MessageFormat& format)
{
    body_format_ = format;
    return *this;
}

MessageHead& MessageHead::SetMessageBodyLen(uint32_t len)
{
    body_len_ = len;
    return *this;
}

MessageRet MessageHead::SerializationJson(parser::ParserJsonObject& parser)
{
    auto head = parser.objectAdd(name_.c_str(), parser::JsonType::OBJECT).Vfind("/" + name_);
    if (!head.isAvailable()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    head.objectAdd("id", mid_);
    if (head.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    head.objectAdd("bodyformat", static_cast<int>(body_format_));
    if (head.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    head.objectAdd("bodylen", static_cast<int>(body_len_));
    if (head.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    return MessageRet::SUCCESS;
}

MessageRet MessageHead::DeserializationJson(parser::ParserJsonObject& parser)
{
    auto head = parser.Vfind("/" + name_);
    if (!head.isAvailable()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    head.Vfind("id").getLong(&mid_);
    if (head.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    head.Vfind("bodyformat").getInt(reinterpret_cast<int*>(&body_format_));
    if (head.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    head.Vfind("bodylen").getInt(reinterpret_cast<int*>(&body_len_));
    if (head.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    return MessageRet::SUCCESS;
}

MessageRet MessageHead::SerializationXml(parser::ParserXml& parser)
{

}
MessageRet MessageHead::DeserializationXml(parser::ParserXml& parser)
{

}

MessageRet MessageHead::SerializationTvl(parser::ParserTvl& parser)
{

}
MessageRet MessageHead::DeserializationTvl(parser::ParserTvl& parser)
{

}

long MessageHead::GenMessageIdByTime()
{
    return time(NULL);
}

}
