#ifndef __MESSAGE_BUILDER_H__
#define __MESSAGE_BUILDER_H__

#include "message_raw.h"
#include "message_tag.h"
#include "message_head.h"
#include "message_body.h"

namespace message {

class MessageBuilder : public MessageRaw {
public:
    MessageBuilder();
    ~MessageBuilder();

    MessageRet SerializationJson(parser::ParserJson& parser);
    MessageRet DeserializationJson(parser::ParserJson& parser);

    MessageRet SerializationXml(parser::ParserXml& parser);
    MessageRet DeserializationXml(parser::ParserXml& parser);

    MessageRet SerializationTvl(parser::ParserTvl& parser);
    MessageRet DeserializationTvl(parser::ParserTvl& parser);
    
private:
    MessageHead head_;
    MessageTag tag_;
};

}

#endif
