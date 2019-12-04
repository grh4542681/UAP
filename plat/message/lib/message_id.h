#ifndef __MESSAGE_ID_H__
#define __MESSAGE_ID_H__

#include <time.h>
#include "message_raw.h"

namespace message {

class MessageId : public MessageRaw{
public:
    MessageId();
    MessageId(MessageId& other);
    ~MessageId();

    MessageId& operator=(const MessageId& other);

    long GetId();

    static MessageId GenMessageIdByTime();
    MessageRet SerializationJson(void* ptr, size_t* size);
    MessageRet DeserializationJson(void* ptr, size_t* size);

    MessageRet SerializationXml(void* ptr, size_t* size);
    MessageRet DeserializationXml(void* ptr, size_t* size);

    MessageRet SerializationTvl(void* ptr, size_t* size);
    MessageRet DeserializationTvl(void* ptr, size_t* size);
private:
    MessageId(long id) {
        id_ = id;
    }

    long id_ = 0;
};

}

#endif
