#include "message_raw.h"

namespace message {

//MessageTag
MessageTag::MessageTag() { }
MessageTag::~MessageTag() { }

int MessageTag::GetLength()
{
    return static_cast<int>(tag_ & MESSAGE_LEN_BIT);
}

MessageFormat MessageTag::GetFormat()
{
    return static_cast<MessageFormat>(((tag_ & MESSAGE_CTRL_BIT) >> 32) & MESSAGE_CTRL_FORMAT_BIT);
}

MessageTag& MessageTag::SetLength(const int& len)
{
    long tmp_len = len;
    tag_ |= tmp_len;
    return *this;
}

MessageTag& MessageTag::SetFormat(const MessageFormat& format)
{
    long tmp_format = format;
    tag_ |= (tmp_format << 32);
    return *this;
}

long MessageTag::BuildTag() {
    return tag_;
}

MessageTag& MessageTag::ParseTag(long tag)
{
    tag_ = tag;
    return *this;
}

//MessageHead
MessageHead::MessageHead() {
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

uint32_t MessageHead::GetMessageBodyLen()
{
    return body_len_;
}

MessageHead& MessageHead::SetMessageAppid(const MessageAppid& appid)
{
    appid_ = appid;
    return *this;
}

MessageHead& MessageHead::SetMessageBodyLen(uint32_t len)
{
    body_len_ = len;
    return *this;
}

long MessageHead::GenMessageIdByTime()
{
    return time(NULL);
}

MessageRaw::MessageRaw(const MessageAppid& appid)
{
    Head.SetMessageAppid(appid);
}

template<> MessageRet MessageRaw::Serialization<parser::ParserJson>(parser::ParserJson& parser)
{
    auto head = parser.find("/").objectAdd("head", parser::JsonType::OBJECT).Vfind("/head");
    if (!head.isAvailable()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    printf("%s : %d\n", __FILE__, __LINE__);
    head.objectAdd("id", Head.mid_);
    if (head.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    head.objectAdd("appid", Head.appid_.Code());
    if (head.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    head.objectAdd("bodylen", static_cast<int>(Head.body_len_));
    if (head.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    auto body = parser.find("/").objectAdd("body", parser::JsonType::OBJECT).Vfind("/body");
    if (!body.isAvailable()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    return SerializationJson(body);
}

template<> MessageRet MessageRaw::Serialization<parser::ParserJsonObject>(parser::ParserJsonObject& parser)
{
    return SerializationJson(const_cast<parser::ParserJsonObject&>(parser));
}

template<> MessageRet MessageRaw::Serialization<parser::ParserXml>(parser::ParserXml& parser)
{
    return SerializationXml(parser);
}

template<> MessageRet MessageRaw::Serialization<parser::ParserTvl>(parser::ParserTvl& parser)
{
    return SerializationTvl(parser);
}

template<> MessageRet MessageRaw::Deserialization<parser::ParserJson>(parser::ParserJson& parser)
{
    auto head = parser.find("/head");
    if (!head.isAvailable()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    head.Vfind("/id").getLong(&(Head.mid_));
    if (head.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    int appid = 0;
    head.Vfind("/appid").getInt(&appid);
    if (head.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    Head.appid_ = appid;
    head.Vfind("/bodylen").getInt(reinterpret_cast<int*>(&(Head.body_len_)));
    if (head.hasError()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    auto body = parser.find("/body");
    if (!body.isAvailable()) {
        return MessageRet::MESSAGE_EPARSER;
    }
    return DeserializationJson(body);
}

template<> MessageRet MessageRaw::Deserialization<parser::ParserJsonObject>(parser::ParserJsonObject& parser)
{
    return DeserializationJson(const_cast<parser::ParserJsonObject&>(parser));
}

template<> MessageRet MessageRaw::Deserialization<parser::ParserXml>(parser::ParserXml& parser)
{
    return DeserializationXml(parser);
}

template<> MessageRet MessageRaw::Deserialization<parser::ParserTvl>(parser::ParserTvl& parser)
{
    return DeserializationTvl(parser);
}

}
