#include "message_agent.h"
#include "message_listener.h"

namespace message {
MessageListener::MessageListener(std::string name, const sock::SockAddress& addr, Callback callback)
{
    agent_ = MessageAgent::getInstance();
    callback_ = callback;
    info_.name_ = name;
    info_.endpoint_num_ = 0;
    info_.address_ = addr;
    info_.state_ = State::Initialize;
    server_ = sock::SockServer(&const_cast<sock::SockAddress&>(addr));
    if (server_.Bind() == sock::SockRet::SUCCESS)
    {
        printf("------- %s %d\n",__FILE__,__LINE__);
        info_.state_ = State::Ready;
        state_ = State::Ready;
    } else {
        printf("------- %s %d\n",__FILE__,__LINE__);
        info_.state_ = State::Error;
        state_ = State::Error;
    }
    sfd_ = server_.GetSockFD();
}

MessageListener::MessageListener(std::string name, const sock::SockFD& sfd, Callback callback)
{
    agent_ = MessageAgent::getInstance();
    callback_ = callback;
    info_.name_ = name;
    info_.endpoint_num_ = 0;
    info_.state_ = State::Initialize;
    info_.state_ = State::Ready;
    sfd_ = sfd;
}

MessageListener::~MessageListener()
{

}

MessageListener::State& MessageListener::GetState()
{
    return state_;
}

sock::SockServer& MessageListener::GetSockServer()
{
    return server_;
}

MessageListener::Callback& MessageListener::GetCallback()
{
    return callback_;
}

bool MessageListener::IsReady()
{
    return (state_ == State::Ready);
}

io::IoRet MessageListener::_common_listener_callback(io::SelectItemTemplate<MessageListener>* item, int events)
{

}

}
