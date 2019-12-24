#ifndef __MESSAGE_HEAD_H__
#define __MESSAGE_HEAD_H__

#include "message_return.h"

#include "message_raw.h"
#include "message_appid.h"

namespace message {

class MessageHead : public MessageRaw {
public:
    MessageHead();
    ~MessageHead();

    long& GetMessageId();
    MessageAppid& GetMessageAppid();
    MessageFormat& GetMessageBodyFormat();
    uint32_t GetMessageBodyLen();

    MessageHead& SetMessageAppid(const MessageAppid& appid);
    MessageHead& SetMessageBodyFormat(const MessageFormat& format);
    MessageHead& SetMessageBodyLen(uint32_t len);

    MessageRet SerializationJson(parser::ParserJsonObject& parser);
    MessageRet DeserializationJson(parser::ParserJsonObject& parser);

    MessageRet SerializationXml(parser::ParserXml& parser);
    MessageRet DeserializationXml(parser::ParserXml& parser);

    MessageRet SerializationTvl(parser::ParserTvl& parser);
    MessageRet DeserializationTvl(parser::ParserTvl& parser);
    
private:
    long mid_;
    MessageAppid appid_;
    MessageFormat body_format_;
    uint32_t body_len_;

    static long GenMessageIdByTime();
};

}

#endif
