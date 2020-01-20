#ifndef __MESSAGE_REMOTE_H__
#define __MESSAGE_REMOTE_H__

#include <string>
#include <atomic>
#include <functional>

#include "io_select_item_template.h"
#include "sock_address.h"
#include "sock_client.h"

#include "message_return.h"
#include "message_log.h"
#include "message_io.h"

namespace message {

class MessageAgent;
class MessageRemote : public MessageIO {
public:
    typedef std::function<io::IoRet(MessageRemote*,io::SelectItemTemplate<MessageRemote>*,int)> Callback;
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
    MessageRemote(std::string remote_machine, std::string remote_listener, std::string remote_endpoint,
                        sock::SockFD& remote_fd, Callback callback = &MessageRemote::_common_remote_callback);
    MessageRemote(std::string remote_machine, std::string remote_listener, std::string remote_endpoint,
                        const sock::SockAddress& remote_address, Callback callback = &MessageRemote::_common_remote_callback);
    ~MessageRemote();

    sock::SockFD& GetRemoteFD();
    State& GetState();
    Callback& GetCallback();

    bool IsReady();

    //Inherited from MessageIO
    MessageRet Recv(MessageRaw* raw);
    MessageRet Send(MessageRaw* raw);
private:
    Info info_;
    State state_;
    std::string remote_uri_;
    sock::SockFD remote_fd_;
    std::atomic_int user_count_;
    Callback callback_;
private:
    MessageRemote(MessageRemote& other);
    const MessageRemote& operator=(const MessageRemote& other);

    io::IoRet _common_remote_callback(io::SelectItemTemplate<MessageRemote>* item, int events);

};

}

#endif
