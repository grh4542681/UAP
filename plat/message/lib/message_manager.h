#ifndef __MESSAGE_MANAGER_H__
#define __MESSAGE_MANAGER_H__

#include "fsm.h"

#include "message_io.h"

namespace message {

class MessageManager : public MessageIO {
public:
    enum class State {
        Initialize,
        Disable,
        Establised,
        Disconnect,
        Error,
    };

    enum class Event {
        Enable,
        Disable,
        Connect,
        Disconnect,
        Reconnect,
    };
public:
    MessageManager(const sock::SockAddress& manager_address);
    MessageManager(const sock::SockFD& manager_fd);
    ~MessageManager();

    //Inherited from MessageIO
    MessageRet Recv(MessageRaw* raw);
    MessageRet Send(MessageRaw* raw);

    ssize_t Read(void* cache, size_t length);
    ssize_t Write(const void* cache, size_t length);
private:
    MessageRet _trigger_event(const Event& event);
private:
    fsm::Fsm<Event, State> fsm_(State::Initialize);

    sock::SockFD manager_fd_;
    sock::SockAddress manager_address_;
};

}

#endif
