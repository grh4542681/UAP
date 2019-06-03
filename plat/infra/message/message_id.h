#ifndef __MESSAGE_ID_H__
#define __MESSAGE_ID_H__

namespace message {

class MessageId {
public:
    MessageId();
    MessageId(MessageId& other);
    ~MessageId();

    std::string toString();
    static MessageID GenMessageID();

};

}

#endif
