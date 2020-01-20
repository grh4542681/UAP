#include "message_manager.h"

namespace message {

MessageManager::MessageManager(const sock::SockAddress& manager_address)
{
    manager_address_ = manager_address;
    _trigger_event(Event::Connect);
    sock::SockClient client(manager_address_);
    if (client.Connect() == sock::SockRet::SUCCESS) {
        manager_fd_ = client.GetSockFD();
    } else {
        MESSAGE_ERROR("Con't connect remote [%s]", remote_uri_.c_str());
        state_ = State::Error;
    }
}

MessageManager::MessageManager(const sock::SockFD& manager_fd) : manager_fd_(manager_fd)
{

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

MessageRet MessageManager::_trigger_event(const Event& event)
{
    return MessageRet::SUCCESS;
}

}
