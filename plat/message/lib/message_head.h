#ifndef __MESSAGE_HEAD_H__
#define __MESSAGE_HEAD_H__

#include "message_id.h"
#include "message_type.h"

namespace message {

class MessageHead {
public:
    friend MessageStreamMemory& operator<<(MessageStreamMemory& ms, MessageHead& mhead);
    friend MessageStreamMemory& operator>>(MessageStreamMemory& ms, MessageHead& mhead);
public:
    MessageHead(MessageType type) {
        mid_ = MessageId::GenMessageIdByTime();
        type_ = type;
        size_ = 0;
    }
    ~MessageHead() {

    }
private:
    MessageId mid_;
    MessageType type_;
    size_t size_;
};

MessageStreamMemory& operator<<(MessageStreamMemory& ms, MessageHead& mhead) {
    ms << mid_;
    ms << type_;
    ms << size_;
    return ms;
}
MessageStreamMemory& operator>>(MessageStreamMemory& ms, MessageHead& mhead) {
    ms >> mid_;
    ms >> type_;
    ms >> size_;
    return ms;
}

}

#endif
