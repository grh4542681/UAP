#ifndef __MESSAGE_LISTENER_SELECT_ITEM_H__
#define __MESSAGE_LISTENER_SELECT_ITEM_H__

#include <string>
#include <utility>
#include <functional>

#include "io_select_item.h"
#include "message_log.h"

namespace message {

class MessageListenerSelectItem : public io::SelectItem {
public:
    MessageListenerSelectItem() : io::SelectItem() { }
    MessageListenerSelectItem(std::string name, sock::SockServer server) : io::SelectItem(fd) {
        listener_name_ = name;
        server_ = server;
        io::SelectItem(server_.GetSockFD());
    }
    ~MessageListenerSelectItem() { }

    const MessageListenerSelectItem& operator=(const MessageListenerSelectItem& other) {
        io::SelectItem::operator=(other);
        listener_name_ = other.listener_name_;
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
                //default input event callback
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
                //default input event callback
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
                //default input event callback
            }
            events |= ~io::SelectEvent::Error;
        }
        return io::IoRet::SUCCESS;
    }

    std::function<MessageRet(MessageListenerSelectItem*)> InputFunc;
    std::function<MessageRet(MessageListenerSelectItem*)> OutputFunc;
    std::function<MessageRet(MessageListenerSelectItem*)> ErrorFunc;
private:
    std::string listener_name_;
    sock::SockServer server_;
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
    MessageRet _default_output_callback_func(MessageListenerSelectItem* select_item) {
        return MessageRet::SUCCESS;
    }
    MessageRet _default_error_callback_func(MessageListenerSelectItem* select_item) {
        return MessageRet::SUCCESS;
    }
};

}

#endif
