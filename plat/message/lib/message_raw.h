#ifndef __MESSAGE_RAW_H__
#define __MESSAGE_RAW_H__

#include "message_return.h"

namespace message {

class MessageRaw {
public:
    MessageRaw() {}
    virtual ~MessageRaw() { }

    virtual MessageRet Serialization(void* ptr, size_t* size) { return MessageRet::ESUBCLASS; }
    virtual MessageRet Deserialization(void* ptr, size_t* size) { return MessageRet::ESUBCLASS; }
};

}

#endif
