#include "message_topology.h"

namespace message {

MessageTopology::Agent::Agent(std::string name, Type type, std::string address, process::ProcessID pid)
    : name_(name), type_(type), address_(address), pid_(pid)
{
    if (type == Type::Local) {
        address_ = "Local";
    }
}

MessageTopology::Agent::~Agent() { }

std::string MessageTopology::Agent::GetName()
{
    return name_;
}

MessageTopology::Agent::Type MessageTopology::Agent::GetType()
{
    return type_;
}

std::string MessageTopology::Agent::GetAddress()
{
    return address_;
}

process::ProcessID MessageTopology::Agent::GetPid()
{
    return pid_;
}

MessageRet MessageTopology::Agent::AddListener(Listener&& listener)
{
    return MessageRet::SUCCESS;
}

MessageRet MessageTopology::Agent::DelListener(std::string name)
{
    return MessageRet::SUCCESS;
}

MessageTopology::Listener* MessageTopology::Agent::FindListener(std::string name)
{
    return NULL;
}

MessageTopology::Listener::Listener(std::string name, sock::SockAddress address)
    : name_(name), address_(address)
{

}

MessageTopology::Listener::~Listener() { }

std::string MessageTopology::Listener::GetName()
{
    return name_;
}

sock::SockAddress MessageTopology::Listener::GetAddress()
{
    return address_;
}

MessageRet MessageTopology::Listener::AddEndpoint(Endpoint&& endpoint)
{
    return MessageRet::SUCCESS;
}

MessageRet DelEndpoint(std::string name)
{
    return MessageRet::SUCCESS;
}

MessageTopology::Endpoint* MessageTopology::Listener::FindEndpoint(std::string name)
{
    return NULL;
}

MessageTopology::Endpoint::Endpoint(std::string name)
    : name_(name)
{

}

MessageTopology::Endpoint::~Endpoint() { }

std::string MessageTopology::Endpoint::GetName()
{
    return name_;
}

MessageTopology::MessageTopology() { }
MessageTopology::~MessageTopology() { }

MessageRet MessageTopology::AddAgent(Agent&& agent)
{
    return MessageRet::SUCCESS;
}
MessageRet MessageTopology::DelAgent(std::string name)
{
    return MessageRet::SUCCESS;
}
MessageTopology::Agent* MessageTopology::FindAgent(std::string name)
{
    return NULL;
}

MessageRet MessageTopology::AddListener(std::string agent, Listener&& listener)
{
    return MessageRet::SUCCESS;
}
MessageRet MessageTopology::DelListener(std::string agent, std::string listener)
{
    return MessageRet::SUCCESS;
}
MessageTopology::Listener* MessageTopology::FindListener(std::string agent, std::string listener)
{
    return NULL;
}

MessageRet MessageTopology::AddEndpoint(std::string agent, std::string listener, Endpoint&& endpoint)
{
    return MessageRet::SUCCESS;
}
MessageRet MessageTopology::DelEndpoint(std::string agent, std::string listener, std::string endpoint)
{
    return MessageRet::SUCCESS;
}
MessageTopology::Endpoint* MessageTopology::FindEndpoint(std::string agent, std::string listener, std::string endpoint)
{
    return NULL;
}
}
