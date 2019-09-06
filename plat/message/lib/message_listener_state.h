#ifndef __MESSAGE_LISTENER_STATE_H__
#define __MESSAGE_LISTENER_STATE_H__

namespace message {

enum class MessageListenerState : int {
    Ready,
    Listening,
    Error,
};

}

#endif
