#ifndef __MESSAGE_INTERNAL_H__
#define __MESSAGE_INTERNAL_H__

#include "mempool.h"

#include "message_raw.h"
#include "message_uri.h"
#include "message_appid.h"
#include "protobuf/message_req_connect.pb.h"

namespace message {

class MessageReqConnect : public MessageRaw, public parser::ParserTvlObject {
public:
    MessageReqConnect() : MessageRaw(MessageAppid::MessageInternal, MessageAppid::MessageReqConnect) { }
    MessageReqConnect(std::string listener, std::string endpoint) : MessageRaw(MessageAppid::MessageInternal, MessageAppid::MessageReqConnect) {
        dest_uri_ = MessageURI("LOCAL", listener, endpoint);
    }
    MessageReqConnect(std::string machine, std::string listener, std::string endpoint) : MessageRaw(MessageAppid::MessageInternal, MessageAppid::MessageReqConnect) {
        dest_uri_ = MessageURI(machine, listener, endpoint);
    }
    MessageReqConnect(const MessageURI& uri) : MessageRaw(MessageAppid::MessageInternal, MessageAppid::MessageReqConnect) {
        dest_uri_ = uri;
    }
    MessageReqConnect(const MessageReqConnect& other) {
        orig_uri_ = other.orig_uri_;
        dest_uri_ = other.dest_uri_;
    }
    ~MessageReqConnect() { }

    parser::ParserTvlObject* Clone() {
        return mempool::MemPool::getInstance()->Malloc<MessageReqConnect>(*this);
    }
    parser::ParserRet BuildTvlString(std::string* str)
    {
        protobuf::MessageReqConnectProtobuf proto;
        proto.set_orig_uri(orig_uri_.GetURI());
        proto.set_dest_uri(dest_uri_.GetURI());
        if (!proto.IsInitialized()) {
            return parser::ParserRet::EINIT;
        }
        if (!proto.SerializeToString(str)) {
            return parser::ParserRet::PARSER_ESERIAL;
        }
        return parser::ParserRet::SUCCESS;
    }
    parser::ParserRet ParseTvlString(const std::string& str)
    {

    }

    MessageRet SerializationJson(parser::ParserJsonObject& parser) {
        parser.objectAdd("orig_uri", orig_uri_.GetURI());
        if (parser.hasError()) {
            return MessageRet::MESSAGE_EPARSER;
        }
        parser.objectAdd("dest_uri", dest_uri_.GetURI());
        if (parser.hasError()) {
            return MessageRet::MESSAGE_EPARSER;
        }
        return MessageRet::SUCCESS;
    }
    MessageRet DeserializationJson(parser::ParserJsonObject& parser) {
        char cache[128];
        memset(cache, 0, sizeof(cache));
        parser.Vfind("/orig_uri").getString(cache, sizeof(cache));
        if (parser.hasError()) {
            return MessageRet::MESSAGE_EPARSER;
        }
        orig_uri_.SetURI(cache);
        memset(cache, 0, sizeof(cache));
        parser.Vfind("/dest_uri").getString(cache, sizeof(cache));
        if (parser.hasError()) {
            return MessageRet::MESSAGE_EPARSER;
        }
        dest_uri_.SetURI(cache);
        return MessageRet::SUCCESS;
    }

    MessageRet SerializationTvl(parser::ParserTvl& parser) {
        parser.PushBack(*this);
        return MessageRet::SUCCESS;
    }
    MessageRet DeserializationTvl(parser::ParserTvl& parser) { return MessageRet::ESUBCLASS; }
private:
    MessageURI orig_uri_;
    MessageURI dest_uri_;
};

}

#endif
