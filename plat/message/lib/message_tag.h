#ifndef __MESSAGE_TAG_H__
#define __MESSAGE_TAG_H__

#include "message_format.h"

namespace message {

class MessageTag {
public:
    MessageTag();
    ~MessageTag();

    MessageFormat& GetFormat();
    MessageTag& SetFormat(const MessageFormat& format);

    long BuildTag();
    MessageTag& ParseTag(long tag);
private:
    MessageFormat format_;
}

}

#endif
