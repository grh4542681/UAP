#ifndef __MESSAGE_ENDPOINT_SELECT_ITEM_H__
#define __MESSAGE_ENDPOINT_SELECT_ITEM_H__

#include <string>
#include <utility>
#include <functional>

#include "io_select_item.h"

namespace message {

class MessageEndpointSelectItem : public io::SelectItem {
public:
    MessageEndpointSelectItem() : io::SelectItem() { }
    MessageEndpointSelectItem(std::string listener_name, std::string endpoint_name, io::FD& fd) : io::SelectItem(fd) {
        listener_name_ = listener_name;
        endpoint_name_ = endpoint_name;
    }
    ~MessageEndpointSelectItem() { }

    const MessageEndpointSelectItem& operator=(const MessageEndpointSelectItem& other) {
        io::SelectItem::operator=(other);
        listener_name_ = other.listener_name_;
        endpoint_name_ = other.endpoint_name_;
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
                //default input event callback
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

    std::function<MessageRet(MessageEndpointSelectItem*)> InputFunc;
    std::function<MessageRet(MessageEndpointSelectItem*)> OutputFunc;
    std::function<MessageRet(MessageEndpointSelectItem*)> ErrorFunc;
private:
    std::string listener_name_;
    std::string endpoint_name_;
};

}

#endif
