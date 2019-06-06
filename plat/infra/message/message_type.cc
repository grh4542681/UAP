#include "message_type.h"

namespace message {

MessageStreamBinary& operator<<(MessageStreamBinary& bs, MessageType& mtype)
{
    bs << mtype;
    return bs;
}

MessageStreamBinary& operator>>(MessageStreamBinary& bs, MessageType& mtype)
{
    bs >> mtype;
    return bs;
}

}
