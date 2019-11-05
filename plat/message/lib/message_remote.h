#ifndef __MESSAGE_REMOTE_H__
#define __MESSAGE_REMOTE_H__

#include <string>
#include <functional>

#include "io_select_item_template.h"
#include "sock_address.h"
#include "sock_client.h"

#include "message_return.h"
#include "message_log.h"

namespace message {

class MessageAgent;
class MessageRemote {
public:
    friend class MessageAgent;
public:
    typedef struct _Info {
        std::string remote_machine_;
        std::string remote_listener_;
        std::string remote_endpoint_;
        sock::SockAddress remote_address_;
    } Info;

    enum class State {
        Initialize,
        Ready,
        Listening,
        Error,
    };

public:
    MessageRemote();
    MessageRemote(std::string remote_machine, std::string remote_listener, std::string remote_endpoint, sock::SockFD& remote_fd);
    MessageRemote(std::string remote_machine, std::string remote_listener, std::string remote_endpoint, const sock::SockAddress& remote_address);
    ~MessageRemote();

    sock::SockFD& GetRemoteFD();
    State& GetState();

    bool IsReady();
private:
    Info info_;
    State state_;
    std::string remote_uri_;
    sock::SockFD remote_fd_;
private:
    MessageRemote(MessageRemote& other);
    const MessageRemote& operator=(const MessageRemote& other);

    io::IoRet _manager_remote_callback(io::SelectItemTemplate<MessageRemote>* item);
    io::IoRet _common_remote_callback(io::SelectItemTemplate<MessageRemote>* item);

};

}

#endif
