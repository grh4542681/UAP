#ifndef __MESSAGE_RAW_H__
#define __MESSAGE_RAW_H__

#include "message_return.h"
#include "message_log.h"

#include "parser_json.h"
#include "parser_tvl.h"
#include "parser_xml.h"

namespace message {

enum class MessageFormat : int {
    Json,
    Xml,
    Tvl,
};

class MessageRaw {
public:
    MessageRaw() {}
    virtual ~MessageRaw() { }

    template <typename P> MessageRet Serialization(P& parser) {
        MESSAGE_ERROR("Unsupport parser type %s", typeid(P).name());
        return MessageRet::MESSAGE_EPARSER;
    }

    template <typename P> MessageRet Deserialization(P& parser) {
        MESSAGE_ERROR("Unsupport parser type %s", typeid(P).name());
        return MessageRet::MESSAGE_EPARSER;
    }

    virtual MessageRet SerializationJson(parser::ParserJson& parser) { return MessageRet::ESUBCLASS; }
    virtual MessageRet DeserializationJson(parser::ParserJson& parser) { return MessageRet::ESUBCLASS; }

    virtual MessageRet SerializationXml(parser::ParserXml& parser) { return MessageRet::ESUBCLASS; }
    virtual MessageRet DeserializationXml(parser::ParserXml& parser) { return MessageRet::ESUBCLASS; }

    virtual MessageRet SerializationTvl(parser::ParserTvl& parser) { return MessageRet::ESUBCLASS; }
    virtual MessageRet DeserializationTvl(parser::ParserTvl& parser) { return MessageRet::ESUBCLASS; }
};

template<> MessageRet MessageRaw::Serialization<parser::ParserJson>(parser::ParserJson& parser);
template<> MessageRet MessageRaw::Serialization<parser::ParserXml>(parser::ParserXml& parser);
template<> MessageRet MessageRaw::Serialization<parser::ParserTvl>(parser::ParserTvl& parser);
template<> MessageRet MessageRaw::Deserialization<parser::ParserJson>(parser::ParserJson& parser);
template<> MessageRet MessageRaw::Deserialization<parser::ParserXml>(parser::ParserXml& parser);
template<> MessageRet MessageRaw::Deserialization<parser::ParserTvl>(parser::ParserTvl& parser);

}

#endif
