#ifndef __MESSAGE_RAW_H__
#define __MESSAGE_RAW_H__

#include "message_return.h"
#include "message_log.h"
#include "message_appid.h"

#include "parser_json.h"
#include "parser_tvl.h"
#include "parser_xml.h"

/*
 * tag:
 *  0xFFFFFFFF FFFFFFFF
 *  | save  || | len  |
 *           T
 */

#define MESSAGE_LEN_BIT (0x00000000FFFFFFFF)

#define MESSAGE_CTRL_BIT (0xFFFFFFFF00000000)
#define MESSAGE_CTRL_FORMAT_BIT (0x0000000F)

namespace message {
class MessageRaw;

enum MessageFormat : int {
    Json = 1,
    Xml,
    Tvl,
};

class MessageTag {
public:
    friend class MessageRaw;
public:
    MessageTag();
    ~MessageTag();

    MessageFormat GetFormat();
    int GetLength();

    MessageTag& SetFormat(const MessageFormat& format);
    MessageTag& SetLength(const int& len);

    long BuildTag();
    MessageTag& ParseTag(long tag);
private:
    long tag_ = 0;
};

class MessageHead : public parser::ParserTvlObject {
public:
    friend class MessageRaw;
public:
    MessageHead();
    MessageHead(const MessageHead& other);
    ~MessageHead();

    const MessageHead& operator=(const MessageHead& other);

    long& GetMessageId();
    MessageAppid& GetMessageComid();
    MessageAppid& GetMessageAppid();
    uint32_t GetMessageBodyLen();

    MessageHead& SetMessageComid(const MessageAppid& comid);
    MessageHead& SetMessageAppid(const MessageAppid& appid);
    MessageHead& SetMessageBodyLen(uint32_t len);

    parser::ParserRet BuildTvlString(std::string* str);
    parser::ParserRet ParseTvlString(const std::string& str);
private:
    long mid_;
    MessageAppid comid_;
    MessageAppid appid_;
    uint32_t body_len_;

    static long GenMessageIdByTime();
};

class MessageRaw {
public:
    MessageRaw();
    MessageRaw(const MessageAppid& comid, const MessageAppid& appid);
    virtual ~MessageRaw() { };

    MessageHead& GetMessageHead();

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
    virtual MessageRet SerializationJson(parser::ParserJsonObject& parser) { return MessageRet::ESUBCLASS; }
    virtual MessageRet DeserializationJson(parser::ParserJsonObject& parser) { return MessageRet::ESUBCLASS; }

    virtual MessageRet SerializationXml(parser::ParserXml& parser) { return MessageRet::ESUBCLASS; }
    virtual MessageRet DeserializationXml(parser::ParserXml& parser) { return MessageRet::ESUBCLASS; }

    virtual MessageRet SerializationTvl(parser::ParserTvl& parser) { return MessageRet::ESUBCLASS; }
    virtual MessageRet DeserializationTvl(parser::ParserTvl& parser) { return MessageRet::ESUBCLASS; }

    MessageHead Head;
};

template<> MessageRet MessageRaw::Serialization<parser::ParserJson>(parser::ParserJson& parser);
template<> MessageRet MessageRaw::Serialization<parser::ParserJsonObject>(parser::ParserJsonObject& parser);
template<> MessageRet MessageRaw::Serialization<parser::ParserXml>(parser::ParserXml& parser);
template<> MessageRet MessageRaw::Serialization<parser::ParserTvl>(parser::ParserTvl& parser);
template<> MessageRet MessageRaw::Deserialization<parser::ParserJson>(parser::ParserJson& parser);
template<> MessageRet MessageRaw::Deserialization<parser::ParserJsonObject>(parser::ParserJsonObject& parser);
template<> MessageRet MessageRaw::Deserialization<parser::ParserXml>(parser::ParserXml& parser);
template<> MessageRet MessageRaw::Deserialization<parser::ParserTvl>(parser::ParserTvl& parser);

}

#endif
