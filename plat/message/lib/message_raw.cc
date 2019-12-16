#include "message_raw.h"

namespace message {

template<> MessageRet MessageRaw::Serialization<parser::ParserJson>(parser::ParserJson& parser)
{
    return SerializationJson(parser);
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
    return DeserializationJson(parser);
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
