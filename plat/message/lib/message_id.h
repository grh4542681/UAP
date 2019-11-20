#ifndef __MESSAGE_ID_H__
#define __MESSAGE_ID_H__

#include <time.h>

namespace message {

class MessageId {
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

}

#endif
