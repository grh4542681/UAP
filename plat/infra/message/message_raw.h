#ifndef __MESSAGE_RAW_H__
#define __MESSAGE_RAW_H__

#include <sstream>

#include "message_return.h"

namespace message {

class MessageRaw {
public:
    MessageRaw();
    virtual ~MessageRaw() { }

    virtual MessageRet Serialization(std::stringstream&& ss) { return MessageRet::ESUBCLASS; }
    virtual MessageRet Deserialization(std::stringstream&& ss) { return MessageRet::ESUBCLASS; }
};

}

#endif
