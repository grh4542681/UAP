#include "message_agent.h"
#include "message_listener.h"

namespace message {
MessageListener::MessageListener(std::string name, sock::SockAddress& addr)
{
    agent_ = MessageAgent::getInstance();
    info_.name_ = name;
    info_.endpoint_num_ = 0;
    info_.address_ = addr;
    info_.state_ = MessageListenerState::Ready;
    server_ = sock::SockServer(&addr);
    server_.Bind();
    select_item_ = MessageListenerSelectItem(info_.name_, server_);
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
