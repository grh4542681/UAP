#ifndef __MESSAGE_BUILDER_H__
#define __MESSAGE_BUILDER_H__

#include "message_header.h"
#include "message_stream.h"

namespace message {

class MessageBuilder {
public:
    MessageBuilder();
    ~MessageBuilder();

private:
    MessageHeader header_;
    MessageStream stream_;
};

}

#endif
