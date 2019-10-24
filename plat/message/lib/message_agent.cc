#include "process_info.h"

#include "message_defines.h"
#include "message_agent.h"

namespace message {

MessageAgent* MessageAgent::pInstance = NULL;

MessageAgent::MessageAgent()
{
    mempool_ = mempool::MemPool::getInstance();
    info_.listener_num_ = 0;
    info_.state_ = State::Initialize;
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

bool MessageAgent::IsReady()
{
    return (info_.state_ == State::Ready);
}

MessageAgent::State& MessageAgent::GetState()
{
    return info_.state_;
}

MessageRemote* MessageAgent::GetRemote()
{
    return remote_manager_;
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

MessageListener* MessageAgent::LookupLinstener(std::string l_name)
{

}

MessageListener* MessageAgent::LookupEndpoint(std::string listener_name, std::string ep_name)
{

}

MessageRet MessageAgent::Run()
{
    process::ProcessInfo* proc = process::ProcessInfo::getInstance();

    auto config_message_enable = proc->GetProcessConfig().GetRoot()->Search<bool>("message/switch");
    if (!config_message_enable) {
        info_.state_ = State::Error;
        MESSAGE_FATAL("Get message config from process error.");
        return MessageRet::ECONFIG;
    }
    bool message_enable = config_message_enable->GetData();
    if (message_enable) {
        std::string protocol = proc->GetProcessConfig().GetRoot()->Search<std::string>("message/manager/address/protocol")->GetData();
        if (protocol == "Father-son") {
            remote_manager_ = mempool_->Malloc<MessageRemote>("LOCAL", "MSG_CTRL", "MSG_CTRL", proc->GetParentProcess()->GetFD());
            MESSAGE_INFO("Create a proxy for communication between father and son");
        } else {
            if (protocol == "local") {
                std::string device = proc->GetProcessConfig().GetRoot()->Search<std::string>("message/manager/address/device")->GetData();
                MESSAGE_INFO("message agent default address [%s] [%s]", protocol.c_str(), device.c_str());
            } else if (protocol == "ipv4") {
                std::string device = proc->GetProcessConfig().GetRoot()->Search<std::string>("message/manager/address/device")->GetData();
                MESSAGE_INFO("message agent default address [%s] [%s]", protocol.c_str(), device.c_str());
            } else if (protocol == "ipv6") {
                std::string device = proc->GetProcessConfig().GetRoot()->Search<std::string>("message/manager/address/device")->GetData();
                MESSAGE_INFO("message agent default address [%s] [%s]", protocol.c_str(), device.c_str());
            }
//    agent_client_ = mempool_->Malloc<MessageRemote>("LOCAL", "MSG_CTRL", "MSG_CTRL", *(message::GetMessageServerAddress()));
        }
    } else {
        info_.state_ = State::Disable;
        MESSAGE_INFO("Function message was disabled.");
        return MessageRet::SUCCESS;
    }
    return MessageRet::SUCCESS;

    if (!remote_manager_ || !remote_manager_->IsReady()) {
        return MessageRet::MESSAGE_AGENT_ECONN;
    }
    info_.state_ = State::Ready;

    remote_manager_->GetSelectItem().GetSelectEvent().SetEvent(io::SelectEvent::Input);
    remote_manager_->GetSelectItem().InputFunc = message_client_callback;

    remote_manager_->GetRemoteFD().Write("hello world", 12);

    select_.AddSelectItem<MessageRemote::SelectItem>(remote_manager_->GetSelectItem());
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
