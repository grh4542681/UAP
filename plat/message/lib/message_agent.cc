#include "mempool.h"

#include "message_defines.h"
#include "message_agent.h"

namespace message {

MessageAgent* MessageAgent::pInstance = NULL;

MessageAgent::MessageAgent()
{
    info_.name_ = process::ProcessInfo::getInstance()->GetName();
    info_.pid_ = process::ProcessInfo::getInstance()->GetPid();
    info_.listener_num_ = 0;
    info_.state_ = MessageAgentState::Ready;
    init_flag_ = true;
}

MessageAgent::~MessageAgent()
{

}

std::string MessageAgent::GetName()
{
    return info_.name_;
}

sock::SockClient& MessageAgent::GetClient()
{
    return client_;
}

MessageRet MessageAgent::Register()
{

}
MessageRet MessageAgent::Unregister()
{

}

MessageRet MessageAgent::Serialization(MessageStreamBinary& bs)
{

}
MessageRet MessageAgent::Deserialization(MessageStreamBinary& bs)
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

MessageRet MessageAgent::RegisterListenEP(MessageListener& lep)
{

}
MessageRet MessageAgent::UnregisterListenEP(std::string name)
{

}

MessageListener* MessageAgent::LookupLinstenEP()
{

}
MessageListener* MessageAgent::LookupLinstenEP(std::string listener_name)
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
    listener_ = thread::ThreadTemplate<decltype(&message_listener_thread), int>(message_listener_thread);
    listener_.Run(this);
    listener_.Detach();

    return MessageRet::SUCCESS;
}

int MessageAgent::message_listener_thread(MessageAgent* msg_agent)
{
    ret::Return ret = MessageRet::SUCCESS;
    msg_agent->GetClient() = sock::SockClient(message::GetMessageServerAddress());
    if ((ret = msg_agent->GetClient().Connect()) != MessageRet::SUCCESS) {
        return MessageRet::MESSAGE_AGENT_ECONN;
    }

    msg_agent->GetClient().GetSockFD().Write("hello world", 12);
/*
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    msg_agent->GetClient().GetSockFD().Recv(NULL,buff,sizeof(buff));
    printf("reply %s\n", buff);
*/

    MessageListener msg_client_listener("MSG_CTRL", msg_agent->client_.GetSockFD());
    msg_client_listener.AddEvent(SELECT_INPUT, message_client_callback);
    msg_agent->select_.AddSelectItem(&msg_client_listener);
//    io::SelectItem msg_client(msg_agent->client_.GetSockFD());
//    msg_client.AddEvent(SELECT_INPUT, message_client_callback);
//    msg_agent->select_.AddSelectItem(&msg_client);

    msg_agent->select_.Initalize();
    msg_agent->select_.Listen(NULL);

    sleep(5);
    return 0;
}

io::IoRet MessageAgent::message_client_callback(io::SelectItem* item)
{
    printf("---callback--\n");
    sock::SockFD* fd = dynamic_cast<sock::SockFD*>(item->GetFdPointer());
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    fd->Recv(NULL,buff,sizeof(buff));
    printf("recv %s\n", buff);
    return io::IoRet::SUCCESS;
}

MessageAgent* MessageAgent::getInstance()
{
    if (!pInstance) {
        pInstance = mempool::MemPool::getInstance()->Malloc<MessageAgent>();
    }
    return pInstance;
}

}
