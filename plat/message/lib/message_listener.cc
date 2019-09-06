#include "message_agent.h"
#include "message_listener.h"

namespace message {
MessageListener::MessageListener(std::string name, io::FD& fd) : io::SelectItem(fd)
{
    agent_ = MessageAgent::getInstance();
    info_.name_ = name;
    info_.agent_name_ = agent_->GetName();
    info_.endpoint_num_ = 0;
    info_.state_ = MessageListenerState::Ready;
}

MessageListener::~MessageListener()
{

}
MessageRet MessageListener::Register()
{

}
MessageRet MessageListener::Unregister()
{

}

}
