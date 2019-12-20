#ifndef __MESSAGE_TAG_H__
#define __MESSAGE_TAG_H__

#include "message_raw.h"

/*
 * tag:
 *  0xFFFFFFFF FFFFFFFF
 *  | save  || | len  |
 *           T
 */

#define MESSAGE_LEN_BIT (0x00000000FFFFFFFF)

#define MESSAGE_CTRL_BIT (0xFFFFFFFF00000000)
#define MESSAGE_CTRL_FORMAT_BIT (0x0000000F)

namespace message {

class MessageTag {
public:
    MessageTag();
    ~MessageTag();

    MessageFormat GetFormat();
    int GetLength();

    MessageTag& SetFormat(const MessageFormat& format);
    MessageTag& SetLength(const int& len);

    long BuildTag();
    MessageTag& ParseTag(long tag);
private:
    long tag_ = 0;
};

}

#endif
