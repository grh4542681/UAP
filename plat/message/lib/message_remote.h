#ifndef __MESSAGE_REMOTE_H__
#define __MESSAGE_REMOTE_H__

namespace message {

class MessageRemote {
public:
    MessageRemote();
    MessageRemote(std::string listener_name, std::string endpoint_name, sock::SockAddress& addr);
    ~MessageRemote();

    
private:
    sock::SockClient;
};

}

#endif
