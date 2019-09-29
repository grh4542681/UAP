#include "message_defines.h"
#include "message_agent.h"

namespace message {

MessageAgent* MessageAgent::pInstance = NULL;

MessageAgent::MessageAgent()
{
    mempool_ = mempool::MemPool::getInstance();
    info_.listener_num_ = 0;
    info_.state_ = MessageAgentState::Ready;
    init_flag_ = true;
}

MessageAgent::~MessageAgent()
{

}

MessageRet MessageAgent::Serialization(MessageStreamBinary& bs)
{

}
MessageRet MessageAgent::Deserialization(MessageStreamBinary& bs)
{

}

sock::SockClient& MessageAgent::GetClient()
{
    return client_;
}

MessageListener* MessageAgent::GetLinstener(std::string l_name)
{

}

MessageEndpoint* MessageAgent::GetEndpoint(std::string listener_name, std::string ep_name)
{

}

MessageRet MessageAgent::RegisterAgent()
{

}

MessageRet MessageAgent::UnregisterAgent()
{

}

template < typename ... Args >
MessageRet MessageAgent::RegisterListener(Args&& ... args)
{
    MessageListener* listener = mempool_->Malloc<MessageListener>(std::forward<Args>(args)...);
}

MessageRet MessageAgent::UnregisterListener(std::string name)
{

}

template < typename ... Args >
MessageRet MessageAgent::RegisterEndpoint(std::string l_name, Args&& ... args)
{

}

MessageRet MessageAgent::UnregisterEP(std::string l_name, std::string e_name)
{

}

MessageLink MessageAgent::LookupLinstener(std::string l_name)
{

}

MessageLink MessageAgent::LookupEndpoint(std::string listener_name, std::string ep_name)
{

}

MessageRet MessageAgent::Run()
{
    MessageRetmote("MSG_CTRL", "MSG_CTRL", message::GetMessageServerAddress());
    client_ = sock::SockClient(message::GetMessageServerAddress());
    if (client_.Connect() != MessageRet::SUCCESS) {
        return MessageRet::MESSAGE_AGENT_ECONN;
    }
    info_.state_ = MessageAgentState::ConnectServer;

    client_.GetSockFD().Write("hello world", 12);
    MessageListener msg_client_listener("MSG_CTRL", client_.GetSockFD());
    msg_client_listener.GetSelectItem().GetSelectEvent().SetEvent(io::SelectEvent::Input);
    msg_client_listener.GetSelectItem().InputFunc = message_client_callback;

    select_.AddSelectItem<MessageListenerSelectItem>(msg_client_listener.GetSelectItem());
    select_.Listen(&timer::Time().SetTime(2, timer::Unit::Second));

    return MessageRet::SUCCESS;
}

MessageRet MessageAgent::message_client_callback(MessageListenerSelectItem* item)
{
    printf("---callback--\n");
    sock::SockFD* fd = dynamic_cast<sock::SockFD*>(item->GetSelectEvent().GetFdPointer());
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    fd->Recv(NULL,buff,sizeof(buff));
    printf("recv %s\n", buff);
    return MessageRet::SUCCESS;
}

MessageAgent* MessageAgent::getInstance()
{
    if (!pInstance) {
        pInstance = mempool::MemPool::getInstance()->Malloc<MessageAgent>();
    }
    return pInstance;
}

}
