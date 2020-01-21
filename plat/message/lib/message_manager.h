#ifndef __MESSAGE_MANAGER_H__
#define __MESSAGE_MANAGER_H__

#include <functional>

#include "fsm.h"
#include "sock_fd.h"
#include "sock_address.h"
#include "io_select_item_template.h"

#include "message_io.h"

namespace message {

class MessageManager : public MessageIO {
public:
    typedef std::function<io::IoRet(MessageManager*,io::SelectItemTemplate<MessageManager>*,int)> SelectCallback;

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
    MessageManager(const sock::SockAddress& manager_address, SelectCallback ReceiveMessageProcessFunc = &MessageManager::_common_receive_message_process);
    MessageManager(const sock::SockFD& manager_fd, SelectCallback ReceiveMessageProcessFunc = &MessageManager::_common_receive_message_process);
    ~MessageManager();

    //Inherited from MessageIO
    MessageRet Recv(MessageRaw* raw);
    MessageRet Send(MessageRaw* raw);

    bool IsAvailable();
    sock::SockFD& GetManagerFD();
    ssize_t Read(void* cache, size_t length);
    ssize_t Write(const void* cache, size_t length);
public:
    SelectCallback ReceiveMessageProcess;
private:
    io::IoRet _common_receive_message_process(io::SelectItemTemplate<MessageManager>* item, int events);
    MessageRet _fsm_init();
    bool _exit_Initialize(fsm::FsmState<MessageManager, State>& next);
    bool _enter_Establised(fsm::FsmState<MessageManager, State>& prev);
    MessageRet _trigger_event(const Event& event);
private:
    fsm::Fsm<MessageManager, Event, State> fsm_;

    sock::SockFD manager_fd_;
    sock::SockAddress manager_address_;
};

}

#endif
