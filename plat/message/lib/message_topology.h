#ifndef __MESSAGE_TOPOLOGY_H__
#define __MESSAGE_TOPOLOGY_H__

#include "sock_address.h"
#include "process_id.h"

#include "message_log.h"
#include "message_return.h"

namespace message {

class MessageTopology {
public:
    class Endpoint {
    public:
        Endpoint(std::string name);
        ~Endpoint();

        std::string GetName();

    private:
        std::string name_;
    };

    class Listener {
    public:
        Listener(std::string name, sock::SockAddress address);
        ~Listener();

        std::string GetName();
        sock::SockAddress GetAddress();

        MessageRet AddEndpoint(Endpoint&& endpoint);
        MessageRet DelEndpoint(std::string name);
        Endpoint* FindEndpoint(std::string name);

    private:
        std::string name_;
        sock::SockAddress address_;
        std::map<std::string, Endpoint> endpoint_map_;
    };

    class Agent {
    public:
        enum class Type {
            Local,
            Remote,
        };
        Agent(std::string name, Type type, std::string address, process::ProcessID pid);
        ~Agent();

        std::string GetName();
        Type GetType();
        std::string GetAddress();
        process::ProcessID GetPid();

        MessageRet AddListener(Listener&& listener);
        MessageRet DelListener(std::string name);
        Listener* FindListener(std::string name);

    private:
        std::string name_;
        Type type_;
        std::string address_;
        process::ProcessID pid_;
        std::map<std::string, Listener> listener_map_;
    };

public:
    MessageTopology();
    ~MessageTopology();

    MessageRet AddAgent(Agent&& agent);
    MessageRet DelAgent(std::string name);
    Agent* FindAgent(std::string name);

    MessageRet AddListener(std::string agent, Listener&& listener);
    MessageRet DelListener(std::string agent, std::string listener);
    Listener* FindListener(std::string agent, std::string listener);

    MessageRet AddEndpoint(std::string agent, std::string listener, Endpoint&& endpoint);
    MessageRet DelEndpoint(std::string agent, std::string listener, std::string endpoint);
    Endpoint* FindEndpoint(std::string agent, std::string listener, std::string endpoint);

private:
    std::map<std::string, Agent> agent_map_;
};

}

#endif
