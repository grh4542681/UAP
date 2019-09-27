#ifndef __MESSAGE_LISTENER_SELECT_ITEM_H__
#define __MESSAGE_LISTENER_SELECT_ITEM_H__

#include <string>
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
        input_func_ = other.input_func_;
        output_func_ = other.output_func_;
        error_func_ = other.error_func_;
        return *this;
    }

    io::IoRet Callback(int events) {
        MessageRet ret = MessageRet::SUCCESS;
        if (events & io::SelectEvent::Input) {
            if (input_func_) {
                ret = input_func_(this);
                if (ret != MessageRet::SUCCESS) {
                    return io::IoRet::IO_EINPUTCB;
                }
            } else {
                //default input event callback
            }
            events |= ~io::SelectEvent::Input;
        }
        if (events & io::SelectEvent::Output) {
            if (output_func_) {
                ret = output_func_(this);
                if (ret != MessageRet::SUCCESS) {
                    return io::IoRet::IO_EOUTPUTCB;
                }
            } else {
                //default input event callback
            }
            events |= ~io::SelectEvent::Output;
        }
        if (events & io::SelectEvent::Error) {
            if (error_func_) {
                ret = error_func_(this);
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

    MessageListenerSelectItem& SetInputFunc(std::function<MessageRet(MessageListenerSelectItem*)>& func) {
        input_func_ = func;
        return *this;
    }
    MessageListenerSelectItem& SetOutputFunc(std::function<MessageRet(MessageListenerSelectItem*)>& func) {
        output_func_ = func;
        return *this;
    }
    MessageListenerSelectItem& SetErrorFunc(std::function<MessageRet(MessageListenerSelectItem*)>& func) {
        error_func_ = func;
        return *this;
    }
private:
    std::string name_;
    std::function<MessageRet(MessageListenerSelectItem*)> input_func_;
    std::function<MessageRet(MessageListenerSelectItem*)> output_func_;
    std::function<MessageRet(MessageListenerSelectItem*)> error_func_;
};

}

#endif
