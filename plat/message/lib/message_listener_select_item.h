#ifndef __MESSAGE_LISTENER_SELECT_ITEM_H__
#define __MESSAGE_LISTENER_SELECT_ITEM_H__

#include <string>
#include <utility>
#include <functional>

#include "io_select_item.h"

namespace message {

class MessageListenerSelectItem : public io::SelectItem {
public:
    MessageListenerSelectItem() : io::SelectItem() { }
    MessageListenerSelectItem(std::string name, io::FD& fd) : io::SelectItem(fd) {
        name_ = name;
    }
    ~MessageListenerSelectItem() { }

    const MessageListenerSelectItem& operator=(const MessageListenerSelectItem& other) {
        io::SelectItem::operator=(other);
        name_ = other.name_;
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

    std::function<MessageRet(MessageListenerSelectItem*)> InputFunc;
    std::function<MessageRet(MessageListenerSelectItem*)> OutputFunc;
    std::function<MessageRet(MessageListenerSelectItem*)> ErrorFunc;
private:
    std::string name_;
};

}

#endif
