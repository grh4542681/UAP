#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "message_type.h"

namespace message {

class Message {
public:
    Message() {
        message_len_ = 0;

    }
    virtual ~Message() {

    }

private:
    size_t message_len_;
    MessageType message_type_;
};

}

#endif
