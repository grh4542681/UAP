#include <time.h>

#include "message_header.h"

namespace message {

MessageHeader::MessageHeader() {
    mid_ = GenMessageIdByTime();
}
MessageHeader::~MessageHeader() {

}

long& MessageHeader::GetMessageId()
{
    return mid_;
}

MessageAppid& MessageHeader::GetMessageAppid()
{
    return appid_;
}

MessageFormat& MessageHeader::GetMessageBodyFormat()
{
    return body_format_;
}

uint32_t MessageHeader::GetMessageBodyLen()
{
    return body_len_;
}

MessageHeader& MessageHeader::SetMessageAppid(const MessageAppid& appid)
{
    appid_ = appid;
    return *this;
}

MessageHeader& MessageHeader::SetMessageBodyFormat(const MessageFormat& format)
{
    body_format_ = format;
    return *this;
}

MessageHeader& MessageHeader::SetMessageBodyLen(uint32_t len)
{
    body_len_ = len;
    return *this;
}

MessageRet MessageHeader::SerializationJson(parser::ParserJson& parser)
{
    auto header = parser.find("/").objectAdd("header", parser::JsonType::OBJECT).Vfind("header");
    if (header.isAvailable()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    header.setObject().objectAdd("id", mid_);
    if (header.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    header.objectAdd("bodyformat", static_cast<int>(body_format_));
    if (header.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    header.objectAdd("bodylen", static_cast<int>(body_len_));
    if (header.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    return MessageRet::SUCCESS;
}

MessageRet MessageHeader::DeserializationJson(parser::ParserJson& parser)
{
    auto header = parser.find("/").objectAdd("header", parser::JsonType::OBJECT);
    if (header.isAvailable()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    header.Vfind("id").getLong(&mid_);
    if (header.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    header.Vfind("bodyformat").getInt(reinterpret_cast<int*>(&body_format_));
    if (header.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    header.Vfind("bodylen").getInt(reinterpret_cast<int*>(&body_len_));
    if (header.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    return MessageRet::SUCCESS;
}

MessageRet MessageHeader::SerializationXml(parser::ParserXml& parser)
{

}
MessageRet MessageHeader::DeserializationXml(parser::ParserXml& parser)
{

}

MessageRet MessageHeader::SerializationTvl(parser::ParserTvl& parser)
{

}
MessageRet MessageHeader::DeserializationTvl(parser::ParserTvl& parser)
{

}

long MessageHeader::GenMessageIdByTime()
{
    return time(NULL);
}

}
