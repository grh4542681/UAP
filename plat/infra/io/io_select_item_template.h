#ifndef __IO_SELECT_ITEM_TEMPLATE_H__
#define __IO_SELECT_ITEM_TEMPLATE_H__

#include <string>
#include <functional>

#include "io_select_item.h"

namespace io {

template < typename HOST = void >
class SelectItemTemplate : public io::SelectItem {
public:
    std::function<IoRet(HOST*, SelectItemTemplate<HOST>*)> InputFunc;
    std::function<IoRet(HOST*, SelectItemTemplate<HOST>*)> OutputFunc;
    std::function<IoRet(HOST*, SelectItemTemplate<HOST>*)> ErrorFunc;
public:
    SelectItemTemplate() : io::SelectItem() { };
    SelectItemTemplate(HOST* host, const FD& fd) : io::SelectItem(fd){
        host_instance_ = host;
    }

    SelectItemTemplate(SelectItemTemplate& other) : io::SelectItem(other) {
        host_instance_ = other.host_instance_;
        InputFunc = other.InputFunc;
        OutputFunc = other.OutputFunc;
        ErrorFunc = other.ErrorFunc;
    }

    virtual ~SelectItemTemplate() {}

    SelectItemTemplate& operator=(SelectItemTemplate& other) {
        io::SelectItem::operator=(other);
        host_instance_ = other.host_instance_;
        InputFunc = other.InputFunc;
        OutputFunc = other.OutputFunc;
        ErrorFunc = other.ErrorFunc;
        return *this;
    }

    io::IoRet Callback(int events) {
        IoRet ret = IoRet::SUCCESS;
        if (events & io::SelectEvent::Input) {
            if (InputFunc) {
                ret = InputFunc(host_instance_, this);
            } else {
                ret = _default_input_callback_func();
            }
            if (ret != IoRet::SUCCESS) {
                return io::IoRet::IO_EINPUTCB;
            }
            printf("-------timer-----\n");
            events |= ~io::SelectEvent::Input;
        }
        if (events & io::SelectEvent::Output) {
            if (OutputFunc) {
                ret = OutputFunc(host_instance_, this);
                if (ret != IoRet::SUCCESS) {
                    return io::IoRet::IO_EOUTPUTCB;
                }
            } else {
            }
            events |= ~io::SelectEvent::Output;
        }
        if (events & io::SelectEvent::Error) {
            if (ErrorFunc) {
                ret = ErrorFunc(host_instance_, this);
                if (ret != IoRet::SUCCESS) {
                    return io::IoRet::IO_EERRCB;
                }
            } else {
            }
            events |= ~io::SelectEvent::Error;
        }
        return io::IoRet::SUCCESS;
    }

    HOST* GetHost() {
        return host_instance_;
    }

    template < typename T > T& GetFd() {
        T& fd = dynamic_cast<T&>(event_.GetFd());
        return fd;
    }

    FD* GetFdPointer() {
        return event_.GetFdPointer();
    }
private:
    HOST* host_instance_ = NULL;

private:
    IoRet _default_input_callback_func() {
        printf("default i callback\n");
        return IoRet::SUCCESS;
    }
    IoRet _default_output_callback_func(SelectItem* select_item) {
        printf("default o callback\n");
        return IoRet::SUCCESS;
    }
    IoRet _default_error_callback_func(SelectItem* select_item) {
        printf("default e callback\n");
        return IoRet::SUCCESS;
    }
};

template < >
class SelectItemTemplate<void> : public io::SelectItem {
public:
    std::function<IoRet(SelectItemTemplate<void>*)> InputFunc;
    std::function<IoRet(SelectItemTemplate<void>*)> OutputFunc;
    std::function<IoRet(SelectItemTemplate<void>*)> ErrorFunc;
public:
    SelectItemTemplate() : io::SelectItem() { };
    SelectItemTemplate(const FD& fd) : io::SelectItem(fd){ }

    SelectItemTemplate(SelectItemTemplate& other) : io::SelectItem(other) {
        InputFunc = other.InputFunc;
        OutputFunc = other.OutputFunc;
        ErrorFunc = other.ErrorFunc;
    }

    ~SelectItemTemplate() {}

    SelectItemTemplate& operator=(SelectItemTemplate& other) {
        io::SelectItem::operator=(other);
        InputFunc = other.InputFunc;
        OutputFunc = other.OutputFunc;
        ErrorFunc = other.ErrorFunc;
        return *this;
    }

    io::IoRet Callback(int events) {
        IoRet ret = IoRet::SUCCESS;
        if (events & io::SelectEvent::Input) {
            if (InputFunc) {
                ret = InputFunc(this);
            } else {
                ret = _default_input_callback_func();
            }
            if (ret != IoRet::SUCCESS) {
                return io::IoRet::IO_EINPUTCB;
            }
            events |= ~io::SelectEvent::Input;
        }
        if (events & io::SelectEvent::Output) {
            if (OutputFunc) {
                ret = OutputFunc(this);
                if (ret != IoRet::SUCCESS) {
                    return io::IoRet::IO_EOUTPUTCB;
                }
            } else {
            }
            events |= ~io::SelectEvent::Output;
        }
        if (events & io::SelectEvent::Error) {
            if (ErrorFunc) {
                ret = ErrorFunc(this);
                if (ret != IoRet::SUCCESS) {
                    return io::IoRet::IO_EERRCB;
                }
            } else {
            }
            events |= ~io::SelectEvent::Error;
        }
        return io::IoRet::SUCCESS;
    }

    template < typename T > T& GetFd() {
        T& fd = dynamic_cast<T&>(event_.GetFd());
        return fd;
    }

    FD* GetFdPointer() {
        return event_.GetFdPointer();
    }
private:
    IoRet _default_input_callback_func() {
        printf("default i callback\n");
        return IoRet::SUCCESS;
    }
    IoRet _default_output_callback_func(SelectItem* select_item) {
        printf("default o callback\n");
        return IoRet::SUCCESS;
    }
    IoRet _default_error_callback_func(SelectItem* select_item) {
        printf("default e callback\n");
        return IoRet::SUCCESS;
    }
};

}

#endif
