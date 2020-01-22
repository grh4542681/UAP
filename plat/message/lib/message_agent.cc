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
    return (manager_ ? true : false);
}

MessageManager* MessageAgent::GetManager()
{
    return manager_;
}

MessageListener* MessageAgent::GetLinstener(std::string l_name)
{

}

MessageEndpoint* MessageAgent::GetEndpoint(std::string listener_name, std::string ep_name)
{

}

MessageRet MessageAgent::UnregisterListener(std::string name)
{

}

MessageRet MessageAgent::UnregisterEP(std::string l_name, std::string e_name)
{

}

MessageListener* MessageAgent::LookupLinstener(std::string listener_name)
{
    auto it = listener_map_.find(listener_name);
    if (it == listener_map_.end()) {
        return NULL;
    }
    return it->second;
}

MessageIO MessageAgent::LookupEndpoint(std::string listener_name, std::string ep_name)
{
    //check local ep

    //check remote ep
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
                RegisterManager(proc->GetParentProcess()->GetFD());
                MESSAGE_INFO("Create a proxy for communication between father and son");
            } else {
                if (protocol == "local") {
                    std::string device = config_message_manager->Search<std::string>("address/device")->GetData();
                    RegisterManager(sock::SockAddress(sock::SockFamily::TCP_LOCAL, device.c_str()));
                    MESSAGE_INFO("message manager default address [%s] [%s]", protocol.c_str(), device.c_str());
                } else if (protocol == "ipv4") {
                    std::string device = config_message_manager->Search<std::string>("address/device")->GetData();
                    MESSAGE_INFO("message manager default address [%s] [%s]", protocol.c_str(), device.c_str());
                } else if (protocol == "ipv6") {
                    std::string device = config_message_manager->Search<std::string>("address/device")->GetData();
                    MESSAGE_INFO("message manager default address [%s] [%s]", protocol.c_str(), device.c_str());
                }
            }
        } else {
            // no message manager.
            if(manager_) {
                mempool_->Free<MessageManager>(manager_);
            }
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
                //listener_map_.insert(default_ep_name, default_listener);
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
