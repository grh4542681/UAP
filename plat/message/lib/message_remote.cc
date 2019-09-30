#include "message_remote.h"

namespace message {

MessageRemote::MessageRemote(std::string remote_machine, std::string remote_listener, std::string remote_endpoint, sock::SockAddress& remote_address)
{
    info_.remote_machine_ = remote_machine.empty() ? "LOCAL" : remote_machine;
    info_.remote_listener_ = remote_listener;
    info_.remote_endpoint_ = remote_endpoint;
    info_.remote_address_ = remote_address;
    remote_uri_ = info_.remote_machine_ + "/" + info_.remote_listener_ + "/" + info_.remote_endpoint_;
    client_ = sock::SockClient(&info_.remote_address_);
    if (client_.Connect() == sock::SockRet::SUCCESS) {
        select_item_ = SelectItem(this);
        state_ = State::Ready;
    } else {
        state_ = State::Error;
    }
}

MessageRemote::~MessageRemote()
{

}

sock::SockClient& MessageRemote::GetSockClient()
{
    return client_;
}

MessageRemote::SelectItem& MessageRemote::GetSelectItem()
{
    return select_item_;
}

MessageRemote::State& MessageRemote::GetState()
{
    return state_;
}

bool MessageRemote::IsReady()
{
    return (state_ == State::Ready);
}

}
