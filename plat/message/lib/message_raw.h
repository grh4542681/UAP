#ifndef __MESSAGE_RAW_H__
#define __MESSAGE_RAW_H__

#include "message_return.h"

namespace message {

class MessageRaw {
public:
    MessageRaw() {}
    virtual ~MessageRaw() { }

    virtual std::string Serialization() { return ""; }
    virtual MesageRet Deserialization(std::string msg) { return MessageRet::ESUBCLASS; }
};

}

#endif
