#ifndef __MESSAGE_HEADER_H__
#define __MESSAGE_HEADER_H__

#include "message_return.h"

#include "message_raw.h"
#include "message_appid.h"

namespace message {

class MessageHeader : public MessageRaw {
public:
    MessageHeader();
    ~MessageHeader();

    long& GetMessageId();
    MessageAppid& GetMessageAppid();
    MessageFormat& GetMessageBodyFormat();
    uint32_t GetMessageBodyLen();

    MessageHeader& SetMessageAppid(const MessageAppid& appid);
    MessageHeader& SetMessageBodyFormat(const MessageFormat& format);
    MessageHeader& SetMessageBodyLen(uint32_t len);

    MessageRet SerializationJson(parser::ParserJson& parser);
    MessageRet DeserializationJson(parser::ParserJson& parser);

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
