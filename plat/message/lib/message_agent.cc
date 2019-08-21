#include "message_defines.h"
#include "message_agent.h"

namespace message {

sock::SockAddress* MessageAgent::MessageServerAddress = NULL;

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

MessageRet MessageAgent::Run()
{
    ret::Return ret = MessageRet::SUCCESS;
    client_ = sock::SockClient(GetMessageServerAddress());
    if ((ret = client_.Connect()) != MessageRet::SUCCESS) {
        return MessageRet::MESSAGE_AGENT_ECONN;
    }

    thread::ThreadTemplate listener_(message_listener_thread);
    listener_.Run(this);
    listener_.Detach();

    return MessageRet::SUCCESS;
}

int MessageAgent::message_listener_thread(MessageAgent* msg_agent)
{
    io::SelectItem& msg_client = msg_agent->select_.GetSelectItem(msg_agent->client_.GetSockFD());
    msg_client.AddEvent(SELECT_OUTPUT, message_client_callback);
    msg_agent->select_.Listen();
    sleep(200);
}

io::IoRet MessageAgent::message_client_callback(io::SelectItem* item)
{

}

sock::SockAddress* MessageAgent::GetMessageServerAddress()
{
    if (!MessageServerAddress) {
        MessageServerAddress = mempool::MemPool::getInstance()->Malloc<sock::SockAddress>(sock::SockFamily::TCP_LOCAL, "/home/ezgaoro/workspace/cppfram/tmp/messaged.sock");
    }
    return MessageServerAddress;
}

}
