#include "message_agent.h"
#include "message_listener.h"

namespace message {
MessageListener::MessageListener(std::string name, io::FD& fd)
{
    agent_ = MessageAgent::getInstance();
    info_.name_ = name;
    info_.endpoint_num_ = 0;
    info_.state_ = MessageListenerState::Ready;
    select_item_ = MessageListenerSelectItem(info_.name_, fd);
}

MessageListener::~MessageListener()
{

}

MessageListenerSelectItem& MessageListener::GetSelectItem()
{
    return select_item_;
}

MessageRet MessageListener::Register()
{

}
MessageRet MessageListener::Unregister()
{

}

}
