#ifndef __MESSAGE_ID_H__
#define __MESSAGE_ID_H__

#include <time.h>

#include "message_stream_binary.h"
#include "message_stream_memory.h"

namespace message {

class MessageId {
public:
    friend MessageStreamBinary& operator<<(MessageStreamBinary& bs, MessageId& mid);
    friend MessageStreamBinary& operator>>(MessageStreamBinary& bs, MessageId& mid);
    friend MessageStreamMemory& operator<<(MessageStreamMemory& ms, MessageId& mid);
    friend MessageStreamMemory& operator>>(MessageStreamMemory& ms, MessageId& mid);
public:
    MessageId() {
        id_ = 0;
    }
    MessageId(MessageId& other) {
        id_ = other.id_;
    }
    ~MessageId() { }

    MessageId& operator=(MessageId& other) {
        id_ = other.id_;
        return *this;
    }

    long GetId() {
        return id_;
    }

    static MessageId GenMessageIdByTime() {
       return MessageId((long)time(NULL));
    }
private:
    MessageId(long id) {
        id_ = id;
    }

    long id_;
};

MessageStreamBinary& operator<<(MessageStreamBinary& bs, MessageId& mid) {
    bs << mid.id_;
    return bs;
}
MessageStreamBinary& operator>>(MessageStreamBinary& bs, MessageId& mid) {
    bs >> mid.id_;
    return bs;
}

MessageStreamMemory& operator<<(MessageStreamMemory& ms, MessageId& mid) {
    ms << mid.id_;
    return ms;
}
MessageStreamMemory& operator>>(MessageStreamMemory& ms, MessageId& mid) {
    ms >> mid.id_;
    return ms;
}

}

#endif
