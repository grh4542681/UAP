#ifndef __MESSAGE_LISTENER_H__
#define __MESSAGE_LISTENER_H__

#include <map>

#include "timer_time.h"
#include "thread_id.h"
#include "sock_address.h"
#include "sock_server.h"
#include "io_select_item.h"

#include "message_return.h"
#include "message_log.h"
#include "message_defines.h"
#include "message_raw.h"
#include "message_endpoint.h"

namespace message {
class MessageAgent;
class MessageListener : public MessageRaw {
public:
    enum class State : int {
        Initialize,
        Ready,
        Listening,
        Error,
    };

    typedef struct _Info {
        std::string name_;
        sock::SockAddress address_;

        int endpoint_num_;
        timer::Time create_time_;
        State state_;
    } Info;

    class SelectItem : public io::SelectItem {
    public:
        SelectItem() : io::SelectItem() { }
        SelectItem(MessageListener* listener) : io::SelectItem(listener->GetSockServer().GetSockFD()) {
            listener_ = listener;
        }
        SelectItem(SelectItem&& other) : io::SelectItem(other) {
            listener_ = other.listener_;
            InputFunc = other.InputFunc;
            OutputFunc = other.OutputFunc;
            ErrorFunc = other.ErrorFunc;
        }
        ~SelectItem() { }

        const SelectItem& operator=(const SelectItem& other) {
            io::SelectItem::operator=(other);
            listener_ = other.listener_;
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
        MessageListener* listener_;
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
    MessageListener(std::string name, sock::SockAddress& addr);
    ~MessageListener();

    SelectItem& GetSelectItem();
    State& GetState();
    sock::SockServer& GetSockServer();

    bool IsReady();

    MessageRet Register();
    MessageRet Unregister();

private:
    MessageAgent* agent_;
    Info info_;
    State state_;
    sock::SockServer server_;
    SelectItem select_item_;
    std::map<std::string, MessageEndpoint*> tep_map_;
private:
    MessageListener(MessageListener& other);
    const MessageListener& operator=(const MessageListener& other);
};

}

#endif
