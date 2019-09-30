#ifndef __MESSAGE_ENDPOINT_H__
#define __MESSAGE_ENDPOINT_H__

#include <string>
#include <functional>

#include "thread_id.h"
#include "sock_fd.h"
#include "io_select_item.h"

#include "message_return.h"
#include "message_defines.h"

namespace message {
class MessageListener;
class MessageEndpoint {
public:
    enum class State {
        Initialize,
        Ready,
        Listening,
        Error,
    };

    typedef struct _Info {
        char name[MESSAGE_ENDPOINT_NAME_MAX_LEN] = { 0 };
        char listener_name[MESSAGE_ENDPOINT_NAME_MAX_LEN] = { 0 };
        thread::ThreadID tid;
        //cond
    } Info;

    class SelectItem : public io::SelectItem {
    public:
        SelectItem() : io::SelectItem() { }
        SelectItem(MessageEndpoint* endpoint, sock::SockFD& fd) : io::SelectItem(fd) {
            endpoint_ = endpoint;
        }
        ~SelectItem() { }

        const SelectItem& operator=(const SelectItem& other) {
            io::SelectItem::operator=(other);
            endpoint_ = other.endpoint_;
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
                    if (ret != MessageRet::SUCCESS) {
                        return io::IoRet::IO_EINPUTCB;
                    }
                } else {
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
        MessageEndpoint* endpoint_;
    };

public:
    MessageEndpoint(std::string name);
    ~MessageEndpoint();

    MessageRet Register();
    MessageRet Unregister();

private:
    MessageListener* listener;
    Info info_;

    std::map<sock::SockFD, SelectItem> select_item_map_;
};

}

#endif

