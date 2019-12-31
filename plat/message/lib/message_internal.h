#ifndef __MESSAGE_INTERNAL_H__
#define __MESSAGE_INTERNAL_H__

#include "message_raw.h"
#include "message_uri.h"
#include "message_appid.h"

namespace message {

class MessageReqConnect : public MessageRaw {
public:
    MessageReqConnect() : MessageRaw(MessageAppid::MessageReqConnect) { }
    MessageReqConnect(std::string listener, std::string endpoint) : MessageRaw(MessageAppid::MessageReqConnect) {
        dest_uri = MessageURI("LOCAL", listener, endpoint);
    }
    MessageReqConnect(std::string machine, std::string listener, std::string endpoint) : MessageRaw(MessageAppid::MessageReqConnect) {
        dest_uri = MessageURI(machine, listener, endpoint);
    }
    MessageReqConnect(const MessageURI& uri) : MessageRaw(MessageAppid::MessageReqConnect) {
        dest_uri = uri;
    }
    ~MessageReqConnect() { }

    MessageRet SerializationJson(parser::ParserJsonObject& parser) {
        parser.objectAdd("orig_uri", orig_uri.GetURI());
        if (parser.hasError()) {
            return MessageRet::MESSAGE_EPARSER;
        }
        parser.objectAdd("dest_uri", dest_uri.GetURI());
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
        orig_uri.SetURI(cache);
        memset(cache, 0, sizeof(cache));
        parser.Vfind("/dest_uri").getString(cache, sizeof(cache));
        if (parser.hasError()) {
            return MessageRet::MESSAGE_EPARSER;
        }
        dest_uri.SetURI(cache);
        return MessageRet::SUCCESS;
    }
private:
    MessageURI orig_uri;
    MessageURI dest_uri;
};

}

#endif
