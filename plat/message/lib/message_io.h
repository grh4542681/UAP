#ifndef __MESSAGE_IO_H__
#define __MESSAGE_IO_H__

#include "message_return.h"
#include "message_raw.h"

namespace message {

class MessageIO {
public:
    MessageIO() { }
    virtual ~MessageIO() { }

    virtual MessageRet Recv(MessageRaw* raw) {
        return MessageRet::ESUBCLASS;
    }
    virtual MessageRet Send(MessageRaw* raw) {
        return MessageRet::ESUBCLASS;
    }
};

}

#endif
