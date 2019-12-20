#include "message_tag.h"

namespace message {

MessageTag::MessageTag() { }
MessageTag::~MessageTag() { }

int MessageTag::GetLength()
{
    return static_cast<int>(tag_ & MESSAGE_LEN_BIT);
}

MessageFormat MessageTag::GetFormat()
{
    return static_cast<MessageFormat>(((tag_ & MESSAGE_CTRL_BIT) >> 32) & MESSAGE_CTRL_FORMAT_BIT);
}

MessageTag& MessageTag::SetLength(const int& len)
{
    long tmp_len = len;
    tag_ |= tmp_len;
    return *this;
}

MessageTag& MessageTag::SetFormat(const MessageFormat& format)
{
    long tmp_format = format;
    tag_ |= (tmp_format << 32);
    return *this;
}

long MessageTag::BuildTag() {
    return tag_;
}

MessageTag& MessageTag::ParseTag(long tag)
{
    tag_ = tag;
    return *this;
}

}
