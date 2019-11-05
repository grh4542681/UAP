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
    auto config_message = proc->GetProcessConfig().GetRoot()->Search("message");
    auto config_message_enable = config_message->Search<bool>("switch");
    if (!config_message_enable) {
        info_.state_ = State::Error;
        MESSAGE_FATAL("Get message config from process error.");
        return MessageRet::ECONFIG;
    }
    bool message_enable = config_message_enable->GetData();
    if (message_enable) {
        auto config_message_manager = config_message->Search("manager");
        auto config_message_manager_enable = config_message_manager->Search<bool>("switch");
        if (!config_message_manager_enable) {
            info_.state_ = State::Error;
            MESSAGE_FATAL("Get message config from process error.");
            return MessageRet::ECONFIG;
        }
        bool message_manager_enable = config_message_manager_enable->GetData();
        if (message_manager_enable) {
            // has message manager will connect.
            std::string protocol = config_message_manager->Search<std::string>("address/protocol")->GetData();
            if (protocol == "Father-son") {
                remote_manager_ = mempool_->Malloc<MessageRemote>("LOCAL", "MSG_CTRL", "MSG_CTRL", proc->GetParentProcess()->GetFD());
                MESSAGE_INFO("Create a proxy for communication between father and son");
            } else {
                if (protocol == "local") {
                    std::string device = config_message_manager->Search<std::string>("address/device")->GetData();
                    remote_manager_ = mempool_->Malloc<MessageRemote>("LOCAL", "MSG_CTRL", "MSG_CTRL", sock::SockAddress(sock::SockFamily::TCP_LOCAL, device.c_str()));
                    MESSAGE_INFO("message agent default address [%s] [%s]", protocol.c_str(), device.c_str());
                } else if (protocol == "ipv4") {
                    std::string device = config_message_manager->Search<std::string>("address/device")->GetData();
                    MESSAGE_INFO("message agent default address [%s] [%s]", protocol.c_str(), device.c_str());
                } else if (protocol == "ipv6") {
                    std::string device = config_message_manager->Search<std::string>("address/device")->GetData();
                    MESSAGE_INFO("message agent default address [%s] [%s]", protocol.c_str(), device.c_str());
                }
    //    agent_client_ = mempool_->Malloc<MessageRemote>("LOCAL", "MSG_CTRL", "MSG_CTRL", *(message::GetMessageServerAddress()));
            }
        } else {
            // no message manager.
            remote_manager_ = NULL;
        }

        auto config_message_agent = config_message->Search("agent");
        if (config_message_agent) {
            // has message agent will listen.
            std::string default_ep_name = config_message_agent->Search<std::string>("name")->GetData();
            if (LookupLinstener(default_ep_name)) {
                return MessageRet::MESSAGE_ELISREPEAT;
            }
            std::string protocol = config_message_agent->Search<std::string>("address/protocol")->GetData();
            if (protocol == "Father-son") {
                /* if this process is child process, sock-pair is used for ctrl ep and listened 
                 * like a remote ep. No need listen again.
                 */
                //MessageListener* default_listener = mempool_->Malloc<MessageListener>(default_ep_name, proc->GetParentProcess()->GetFD());
                //listen_local_ep_map_.insert(default_ep_name, default_listener);
                MESSAGE_INFO("Child process no need listen agent EP, just use MSG_CTRL EP.");
            } else {
                if (protocol == "local") {
                    std::string device_file = config_message_agent->Search<std::string>("address/device")->GetData();
                    MessageListener* default_listener = mempool_->Malloc<MessageListener>(
                                    "LOCAL", "MSG_CTRL", "MSG_CTRL", sock::SockAddress(sock::SockFamily::TCP_LOCAL, device.c_str()));
                    RegisterListener(default_listener);
                    MESSAGE_INFO("message agent default address [%s] [%s]", protocol.c_str(), device.c_str());
                } else if (protocol == "ipv4") {
                    std::string device = config_message_agent->Search<std::string>("address/device")->GetData();
                    MESSAGE_INFO("message agent default address [%s] [%s]", protocol.c_str(), device.c_str());
                } else if (protocol == "ipv6") {
                    std::string device = config_message_agent->Search<std::string>("address/device")->GetData();
                    MESSAGE_INFO("message agent default address [%s] [%s]", protocol.c_str(), device.c_str());
                }
    //    agent_client_ = mempool_->Malloc<MessageRemote>("LOCAL", "MSG_CTRL", "MSG_CTRL", *(message::GetMessageServerAddress()));
            }
        } else {
            // no message agent.
        }
    } else {
        info_.state_ = State::Disable;
        MESSAGE_INFO("Function message was disabled.");
        return MessageRet::SUCCESS;
    }
    return MessageRet::SUCCESS;

    if (remote_manager_) {
        if (!remote_manager_->IsReady()) {
            return MessageRet::MESSAGE_AGENT_ECONN;
        }
        info_.state_ = State::Listenning;

        io::SelectItemTemplate<MessageRemote> manager_selectitem(remote_manager_, remote_manager_->GetRemoteFD());

        manager_selectitem.GetSelectEvent().SetEvent(io::SelectEvent::Input);
        manager_selectitem.InputFunc = &MessageRemote::_manager_remote_callback;

        remote_manager_->GetRemoteFD().Write("hello world", 12);

        select_.AddSelectItem<io::SelectItemTemplate<MessageRemote>>(manager_selectitem);

    }
    timer::Time t;
    t.SetTime(2, timer::Unit::Second);
    printf("----%d---\n",t.GetSecond());
    select_.ListenThread(t);
    //select_.Listen(&timer::Time().SetTime(2, timer::Unit::Second));

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
