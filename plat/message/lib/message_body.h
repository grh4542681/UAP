#ifndef __MESSAGE_BODY_H__
#define __MESSAGE_BODY_H__

#include "message_raw.h"

namespace message {

class MessageBody : public MessageRaw {
public:
    MessageBody();
    ~MessageBody();

};

}

#endif
