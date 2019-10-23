#ifndef __MESSAGE_REMOTE_H__
#define __MESSAGE_REMOTE_H__

#include <string>
#include <functional>

#include "io_select_item.h"
#include "sock_address.h"
#include "sock_client.h"

#include "message_return.h"
#include "message_log.h"

namespace message {

class MessageRemote {
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

    class SelectItem : public io::SelectItem {
    public:
        SelectItem() : io::SelectItem() { }
        SelectItem(MessageRemote* remote) : io::SelectItem(remote->GetRemoteFD()) {
            remote_ = remote;
        }
        SelectItem(SelectItem& other): io::SelectItem(other) {
            remote_ = other.remote_;
            InputFunc = other.InputFunc;
            OutputFunc = other.OutputFunc;
            ErrorFunc = other.ErrorFunc;
        }
        ~SelectItem() { }

        SelectItem& operator=(SelectItem&& other) {
            io::SelectItem::operator=(other);
            remote_ = other.remote_;
            InputFunc = other.InputFunc;
            OutputFunc = other.OutputFunc;
            ErrorFunc = other.ErrorFunc;
            return *this;
        }

        io::IoRet Callback(int events) {
            MessageRet ret = MessageRet::SUCCESS;
            if (events & io::SelectEvent::Input) {
                if (InputFunc) {
                    ret = InputFunc(this);
                } else {
                    ret = _default_input_callback_func();
                }
                if (ret != MessageRet::SUCCESS) {
                    return io::IoRet::IO_EINPUTCB;
                }
                events |= ~io::SelectEvent::Input;
            }
            if (events & io::SelectEvent::Output) {
                if (OutputFunc) {
                    ret = OutputFunc(this);
                    if (ret != MessageRet::SUCCESS) {
                        return io::IoRet::IO_EOUTPUTCB;
                    }
                } else {
                }
                events |= ~io::SelectEvent::Output;
            }
            if (events & io::SelectEvent::Error) {
                if (ErrorFunc) {
                    ret = ErrorFunc(this);
                    if (ret != MessageRet::SUCCESS) {
                        return io::IoRet::IO_EERRCB;
                    }
                } else {
                }
                events |= ~io::SelectEvent::Error;
            }
            return io::IoRet::SUCCESS;
        }

        std::function<MessageRet(SelectItem*)> InputFunc;
        std::function<MessageRet(SelectItem*)> OutputFunc;
        std::function<MessageRet(SelectItem*)> ErrorFunc;
    private:
        MessageRemote* remote_;
        MessageRet _default_input_callback_func() {
            printf("default callback\n");
            sock::SockFD* sockfd = dynamic_cast<sock::SockFD*>(event_.GetFdPointer());
            if (!sockfd) {
                MESSAGE_ERROR("Listening file descriptor is NULL.");
                return MessageRet::MESSAGE_LISTEN_EFD;
            }
            char buff[1024];
            memset(buff, 0, sizeof(buff));
            sockfd->Recv(NULL,buff,sizeof(buff));
            printf("recv %s\n", buff);
            return MessageRet::SUCCESS;
        }
        MessageRet _default_output_callback_func(SelectItem* select_item) {
            return MessageRet::SUCCESS;
        }
        MessageRet _default_error_callback_func(SelectItem* select_item) {
            return MessageRet::SUCCESS;
        }
    };

public:
    MessageRemote();
    MessageRemote(std::string remote_machine, std::string remote_listener, std::string remote_endpoint, sock::SockFD& remote_fd);
    MessageRemote(std::string remote_machine, std::string remote_listener, std::string remote_endpoint, sock::SockAddress& remote_address);
    ~MessageRemote();

    sock::SockFD& GetRemoteFD();
    SelectItem& GetSelectItem();
    State& GetState();

    bool IsReady();
private:
    Info info_;
    State state_;
    std::string remote_uri_;
    sock::SockFD remote_fd_;
    SelectItem select_item_;
private:
    MessageRemote(MessageRemote& other);
    const MessageRemote& operator=(const MessageRemote& other);

};

}

#endif
