#include "message_agent.h"
#include "message_listener.h"

namespace message {
MessageListener::MessageListener(std::string name, io::FD& fd)
{
    event_ = io::SelectEvent(fd, io::SelectEvent::Input);
    agent_ = MessageAgent::getInstance();
    info_.name_ = name;
    info_.endpoint_num_ = 0;
    info_.state_ = MessageListenerState::Ready;
}

MessageListener::~MessageListener()
{

}

io::SelectEvent& MessageListener::GetEvent()
{
    return event_;
}

MessageRet MessageListener::Register()
{

}
MessageRet MessageListener::Unregister()
{

}

}
