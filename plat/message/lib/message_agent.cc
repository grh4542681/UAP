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

MessageRemote* MessageAgent::GetRemote()
{
    return agent_client_;
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
    agent_client_ = mempool_->Malloc<MessageRemote>("LOCAL", "MSG_CTRL", "MSG_CTRL", *(message::GetMessageServerAddress()));
    if (!agent_client_ || !agent_client_->IsReady()) {
        return MessageRet::MESSAGE_AGENT_ECONN;
    }
    info_.state_ = MessageAgentState::ConnectServer;

    agent_client_->GetSelectItem().GetSelectEvent().SetEvent(io::SelectEvent::Input);
    agent_client_->GetSelectItem().InputFunc = message_client_callback;

    agent_client_->GetSockClient().GetSockFD().Write("hello world", 12);

    select_.AddSelectItem<MessageRemote::SelectItem>(agent_client_->GetSelectItem());
    timer::Time t;
    t.SetTime(2, timer::Unit::Second);
    printf("----%d---\n",t.GetSecond());
    select_.Listen(t);
    //select_.Listen(&timer::Time().SetTime(2, timer::Unit::Second));

    return MessageRet::SUCCESS;
}

MessageRet MessageAgent::message_client_callback(MessageRemote::SelectItem* item)
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
