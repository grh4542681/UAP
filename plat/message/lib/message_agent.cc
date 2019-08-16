#include "sock_address.h"
#include "sock_client.h"

#include "message_agent.h"

namespace message {

MessageAgent::MessageAgent(std::string name)
{
    if (name.length() > MESSAGE_ENDPOINT_NAME_MAX_LEN) {
        info_.state_ = MessageAgentState::Error;
        init_flag_ = false;
    } else {
        memcpy(info_.name_, name.c_str(), name.length());
        info_.pid_ = process::ProcessID::GetProcessID();
        info_.state_ = MessageAgentState::Ready;
        init_flag_ = true;
    }
}

MessageAgent::~MessageAgent()
{

}

MessageRet MessageAgent::RegisterEP(MessageEndpoint& ep)
{

}
MessageRet MessageAgent::RegisterEP(std::string name, MessageEndpoint& ep)
{

}
MessageRet MessageAgent::UnregisterEP(MessageEndpoint& ep)
{

}
MessageRet MessageAgent::UnregisterEP(std::string listener_name, std::string ep_name)
{

}

MessageRet MessageAgent::RegisterListenEP(MessageListenEndpoint& lep)
{

}
MessageRet MessageAgent::UnregisterListenEP(std::string name)
{

}

MessageListenEndpoint* MessageAgent::LookupLinstenEP()
{

}
MessageListenEndpoint* MessageAgent::LookupLinstenEP(std::string listener_name)
{

}

MessageEndpoint* MessageAgent::LookupEP(std::string ep_name)
{

}
MessageEndpoint* MessageAgent::LookupEP(std::string listener_name, std::string ep_name)
{

}

void MessageAgent::Run()
{
    thread::ThreadTemplate listener_(message_listener_thread);
    listener_.Run(this);
    listener_.Detach();
}

MessageRet MessageAgent::_connect_server()
{
    sock::SockAddress msgd_address(sock::SockFamily::TCP_LOCAL, MESSAGE_DEAMON_SOCK_FILE);
    sock::SockClient agent(msgd_address);
    sock::SockFD* msgd_fd = agent.Connect();

    MessageListenEndpoint()
}

int MessageAgent::message_listener_thread(MessageAgent* mg)
{

}

}
