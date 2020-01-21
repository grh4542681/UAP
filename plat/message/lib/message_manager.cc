#include "message_manager.h"

#include "sock_client.h"

namespace message {

MessageManager::MessageManager(const sock::SockAddress& manager_address, SelectCallback ReceiveMessageProcessFunc)
                : ReceiveMessageProcess(ReceiveMessageProcessFunc), fsm_(State::Initialize, this)
{
    manager_address_ = manager_address;


    _trigger_event(Event::Connect);
//    sock::SockClient client(&manager_address_);
//    if (client.Connect() == sock::SockRet::SUCCESS) {
//        manager_fd_ = client.GetSockFD();
//    } else {
//    }
}

MessageManager::MessageManager(const sock::SockFD& manager_fd, SelectCallback ReceiveMessageProcessFunc)
                : ReceiveMessageProcess(ReceiveMessageProcessFunc), fsm_(State::Initialize, this)
{
    manager_fd_ = manager_fd;
    if (manager_fd_.Available()) {
        fsm_.ChangeStateForce(State::Establised);
    } else {
        fsm_.ChangeStateForce(State::Error);
    }
}

MessageManager::~MessageManager() { }

//Inherited from MessageIO
MessageRet MessageManager::Recv(MessageRaw* raw)
{
    return MessageRet::SUCCESS;
}

MessageRet MessageManager::Send(MessageRaw* raw)
{
    return MessageRet::SUCCESS;
}

bool MessageManager::IsAvailable()
{
    return (fsm_.GetState() == State::Establised);
}

sock::SockFD& MessageManager::GetManagerFD()
{
    return manager_fd_;
}

ssize_t MessageManager::Read(void* cache, size_t length)
{
    if (fsm_.GetState() != State::Establised) {
        return MessageRet::MESSAGE_MANAGER_ESTATE;
    }
    if (!manager_fd_.Available()) {
        return MessageRet::MESSAGE_MANAGER_ESOCK;
    }
    return manager_fd_.Read(cache, length);
}

ssize_t MessageManager::Write(const void* cache, size_t length)
{
    if (fsm_.GetState() != State::Establised) {
        return MessageRet::MESSAGE_MANAGER_ESTATE;
    }
    if (!manager_fd_.Available()) {
        return MessageRet::MESSAGE_MANAGER_ESOCK;
    }
    return manager_fd_.Write(cache, length);
}

io::IoRet MessageManager::_common_receive_message_process(io::SelectItemTemplate<MessageManager>* item, int events)
{
    return io::IoRet::SUCCESS;
}

MessageRet MessageManager::_trigger_event(const Event& event)
{
    return MessageRet::SUCCESS;
}

bool MessageManager::_exit_Initialize(fsm::FsmState<MessageManager, State>& next)
{
    MESSAGE_INFO("Message manager exit Initialize state");
    return true;
}

bool MessageManager::_enter_Establised(fsm::FsmState<MessageManager, State>& prev)
{
    MESSAGE_INFO("Message manager enter Establised state");
    return true;
}

MessageRet MessageManager::_fsm_init()
{
    fsm::FsmEvent<MessageManager, Event>* pevent = NULL;
    fsm::FsmState<MessageManager, State>* pstate = NULL;

    fsm_.Clear();

    fsm_.AddEvent(fsm::FsmEvent<MessageManager, Event>(Event::Enable));
    fsm_.AddEvent(fsm::FsmEvent<MessageManager, Event>(Event::Disable));
    fsm_.AddEvent(fsm::FsmEvent<MessageManager, Event>(Event::Connect));
    fsm_.AddEvent(fsm::FsmEvent<MessageManager, Event>(Event::Disconnect));
    fsm_.AddEvent(fsm::FsmEvent<MessageManager, Event>(Event::Reconnect));
    
    fsm_.AddState(fsm::FsmState<MessageManager, State>(State::Initialize));
    pstate = fsm_.GetState(State::Initialize);
    if (pstate) {
        pstate->Exit = &MessageManager::_exit_Initialize;
    } else {
        goto _fsm_init_error;
    }
    fsm_.AddState(fsm::FsmState<MessageManager, State>(State::Disable));
    fsm_.AddState(fsm::FsmState<MessageManager, State>(State::Establised));
    pstate = fsm_.GetState(State::Establised);
    if (pstate) {
        pstate->Enter = &MessageManager::_enter_Establised;
    }
    fsm_.AddState(fsm::FsmState<MessageManager, State>(State::Disconnect));
    fsm_.AddState(fsm::FsmState<MessageManager, State>(State::Error));


    fsm_.AddTransition(fsm::FsmTransition<MessageManager, Event, State>(Event::Connect, State::Initialize, State::Establised));

    return MessageRet::SUCCESS;

_fsm_init_error:
    fsm_.Clear();
    fsm_.ChangeStateForce(State::Error);
    return MessageRet::EINIT;
}

}
