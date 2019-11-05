#include "message_agent.h"
#include "message_listener.h"

namespace message {
MessageListener::MessageListener(std::string name, sock::SockAddress& addr)
{
    agent_ = MessageAgent::getInstance();
    info_.name_ = name;
    info_.endpoint_num_ = 0;
    info_.address_ = addr;
    info_.state_ = State::Initialize;
    server_ = sock::SockServer(&addr);
    if (server_.Bind() == sock::SockRet::SUCCESS)
    {
        info_.state_ = State::Ready;
        state_ = State::Ready;
    } else {
        info_.state_ = State::Error;
        state_ = State::Error;
    }
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

bool MessageListener::IsReady()
{
    return (state_ == State::Ready);
}

}
