#include "message_remote.h"

namespace message {

MessageRemote::MessageRemote(std::string remote_machine, std::string remote_listener, std::string remote_endpoint, const sock::SockAddress& remote_address, Callback callback)
        : MessageIO()
{
    info_.remote_machine_ = remote_machine.empty() ? "LOCAL" : remote_machine;
    info_.remote_listener_ = remote_listener;
    info_.remote_endpoint_ = remote_endpoint;
    info_.remote_address_ = remote_address;
    remote_uri_ = info_.remote_machine_ + "/" + info_.remote_listener_ + "/" + info_.remote_endpoint_;
    sock::SockClient client(&info_.remote_address_);
    if (client.Connect() == sock::SockRet::SUCCESS) {
        remote_fd_ = client.GetSockFD();
        state_ = State::Ready;
    } else {
        MESSAGE_ERROR("Con't connect remote [%s]", remote_uri_.c_str());
        state_ = State::Error;
    }
    callback_ = callback;
}

MessageRemote::MessageRemote(std::string remote_machine, std::string remote_listener, std::string remote_endpoint, sock::SockFD& remote_fd, Callback callback)
        : MessageIO()
{
    info_.remote_machine_ = remote_machine.empty() ? "LOCAL" : remote_machine;
    info_.remote_listener_ = remote_listener;
    info_.remote_endpoint_ = remote_endpoint;
    info_.remote_address_ = remote_fd.GetDestAddress();
    remote_uri_ = info_.remote_machine_ + "/" + info_.remote_listener_ + "/" + info_.remote_endpoint_;
    remote_fd_ = remote_fd;
    state_ = State::Ready;
    callback_ = callback;
}

MessageRemote::~MessageRemote()
{

}

sock::SockFD& MessageRemote::GetRemoteFD()
{
    return remote_fd_;
}

MessageRemote::State& MessageRemote::GetState()
{
    return state_;
}

MessageRemote::Callback& MessageRemote::GetCallback()
{
    return callback_;
}

bool MessageRemote::IsReady()
{
    return (state_ == State::Ready);
}

MessageRet MessageRemote::Recv(MessageRaw* raw)
{
    return MessageRet::SUCCESS;
}

MessageRet MessageRemote::Send(MessageRaw* raw)
{
    return MessageRet::SUCCESS;
}

io::IoRet MessageRemote::_common_remote_callback(io::SelectItemTemplate<MessageRemote>* item, int events)
{
    printf("---callback--\n");
    auto fd = item->template GetFd<sock::SockFD>();
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    fd.Recv(NULL,buff,sizeof(buff));
    printf("recv %s\n", buff);
    return MessageRet::SUCCESS;
}

}
