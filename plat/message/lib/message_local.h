#ifndef __MESSAGE_LOCAL_H__
#define __MESSAGE_LOCAL_H__

#include "message_io.h"

namespace message {

class MessageLocal : public MessageIO {
public:
    MessageLocal();
    ~MessageLocal();

    //Inherited from MessageIO
    MessageRet Recv(MessageRaw* raw);
    MessageRet Send(MessageRaw* raw);
};

}

#endif
