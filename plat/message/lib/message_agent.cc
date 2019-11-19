#include "process_info.h"

#include "message_defines.h"
#include "message_agent.h"

namespace message {

MessageAgent* MessageAgent::pInstance = NULL;
std::string MessageAgent::DefaultName = "";

MessageAgent::MessageAgent()
{
    mempool_ = mempool::MemPool::getInstance();
    info_.listener_num_ = 0;
    info_.state_ = State::Initialize;
    type_ = Type::NormalAgent;
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

MessageAgent::Type& MessageAgent::GetType()
{
    return type_;
}

MessageAgent& MessageAgent::SetType(const MessageAgent::Type& type)
{
    type_ = type;
    return *this;
}

bool MessageAgent::HasManager()
{
    return (remote_manager_ ? true : false);
}

MessageRemote* MessageAgent::GetManager()
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

MessageRet MessageAgent::RegisterListener(std::string name, const sock::SockAddress& addr)
{
    if (LookupLinstener(name)) {
        return MessageRet::MESSAGE_LISTENER_EREPEAT;
    }
    MessageListener* listener = NULL;
    switch (type_) {
        case Type::NormalAgent:
            listener = mempool_->Malloc<MessageListener>(name, addr, MessageListener::Type::NormalListener);
            if (!listener) {
                return MessageRet::EMALLOC;
            }
            if (!(listener->IsReady())) {
                mempool_->Free<MessageListener>(listener);
                return MessageRet::MESSAGE_LISTENER_ESTATE;
            }
            {
                io::SelectItemTemplate<MessageListener> listener_selectitem(listener, listener->GetSockServer().GetSockFD());
                listener_selectitem.GetSelectEvent().SetEvent(io::SelectEvent::Input);
                listener_selectitem.InputFunc = &MessageListener::_common_listener_callback;
                select_.AddSelectItem<io::SelectItemTemplate<MessageListener>>(listener_selectitem);
            }
            break;
        case Type::KeeperAgent:
            listener = mempool_->Malloc<MessageListener>(name, addr, MessageListener::Type::KeeperListener);
            if (!listener) {
                return MessageRet::EMALLOC;
            }
            if (!(listener->IsReady())) {
                mempool_->Free<MessageListener>(listener);
                return MessageRet::MESSAGE_LISTENER_ESTATE;
            }
            break;
        case Type::WorkerAgent:
            listener = mempool_->Malloc<MessageListener>(name, addr, MessageListener::Type::WorkerListener);
            if (!listener) {
                return MessageRet::EMALLOC;
            }
            if (!(listener->IsReady())) {
                mempool_->Free<MessageListener>(listener);
                return MessageRet::MESSAGE_LISTENER_ESTATE;
            }
            break;
        default:
            return MessageRet::ERROR;
    }

    listen_local_ep_map_.insert({name, listener});
    return MessageRet::SUCCESS;
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

MessageListener* MessageAgent::LookupLinstener(std::string listener_name)
{
    auto it = listen_local_ep_map_.find(listener_name);
    if (it == listen_local_ep_map_.end()) {
        return NULL;
    }
    return it->second;
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
            if (protocol == "Keeper-Worker") {
                type_ = Type::WorkerAgent;
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
            }
            if (!remote_manager_->IsReady()) {
                return MessageRet::MESSAGE_AGENT_ECONN;
            }
            io::SelectItemTemplate<MessageRemote> manager_selectitem(remote_manager_, remote_manager_->GetRemoteFD());
            manager_selectitem.GetSelectEvent().SetEvent(io::SelectEvent::Input);
            manager_selectitem.InputFunc = &MessageRemote::_manager_remote_callback;
            remote_manager_->GetRemoteFD().Write("hello world", 12);
            select_.AddSelectItem<io::SelectItemTemplate<MessageRemote>>(manager_selectitem);
        } else {
            // no message manager.
            remote_manager_ = NULL;
        }

        auto config_message_agent = config_message->Search("agent");
        if (config_message_agent) {
            // has message agent will listen.
            std::string default_ep_name = config_message_agent->Search<std::string>("name")->GetData();
            if (LookupLinstener(default_ep_name)) {
                return MessageRet::MESSAGE_LISTENER_EREPEAT;
            }
            
            std::string protocol = config_message_agent->Search<std::string>("address/protocol")->GetData();
            if (protocol == "Keeper-Worker") {
                /* if this process is child process, sock-pair is used for ctrl ep and listened 
                 * like a remote ep. No need listen again.
                 */
                //MessageListener* default_listener = mempool_->Malloc<MessageListener>(default_ep_name, proc->GetParentProcess()->GetFD());
                //listen_local_ep_map_.insert(default_ep_name, default_listener);
                MESSAGE_INFO("Child process no need listen agent EP, just use MSG_CTRL EP.");
            } else {
                if (protocol == "local") {
                    std::string device_file = config_message_agent->Search<std::string>("address/device")->GetData();
                    RegisterListener(default_ep_name, sock::SockAddress(sock::SockFamily::TCP_LOCAL, device_file.c_str()));
                    MESSAGE_INFO("message agent default address [%s] [%s]", protocol.c_str(), device_file.c_str());
                } else if (protocol == "ipv4") {
                    std::string device = config_message_agent->Search<std::string>("address/device")->GetData();
                    MESSAGE_INFO("message agent default address [%s] [%s]", protocol.c_str(), device.c_str());
                } else if (protocol == "ipv6") {
                    std::string device = config_message_agent->Search<std::string>("address/device")->GetData();
                    MESSAGE_INFO("message agent default address [%s] [%s]", protocol.c_str(), device.c_str());
                }
            }
            DefaultName = default_ep_name;
        } else {
            // no message agent.
        }
    } else {
        info_.state_ = State::Disable;
        MESSAGE_INFO("Function message was disabled.");
        return MessageRet::SUCCESS;
    }
    auto select_ret = select_.ListenThread(timer::Time());
    if (select_ret != io::IoRet::SUCCESS) {
        return MessageRet::MESSAGE_ESELECT;
    }
    info_.state_ = State::Ready;
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
