#ifndef __MESSAGE_URI_H__
#define __MESSAGE_URI_H__

#include <string>
#include "string/string_util.h"

namespace message {

class MessageURI {
public:
    MessageURI() { }
    MessageURI(std::string machine, std::string listener, std::string endpoint) {
        machine_ = machine;
        listener_ = listener;
        endpoint_ = endpoint;
    }
    MessageURI(const MessageURI& other) {
        machine_ = other.machine_;
        listener_ = other.listener_;
        endpoint_ = other.endpoint_;
    }
    ~MessageURI() { }

    const MessageURI& operator= (const MessageURI& other) {
        machine_ = other.machine_;
        listener_ = other.listener_;
        endpoint_ = other.endpoint_;
        return *this;
    }

    MessageURI& SetMachine(std::string machine) {
        machine_ = machine;
        return *this;
    }

    MessageURI& SetListener(std::string listener) {
        listener_ = listener;
        return *this;
    }
    
    MessageURI& SetEndpoint(std::string endpoint) {
        endpoint_ = endpoint;
        return *this;
    }

    std::string GetMachine() {
        return machine_;
    }
    
    std::string GetListener() {
        return listener_;
    }

    std::string GetEndpoint() {
        return endpoint_;
    }

    std::string GetURI() {
        return (machine_ + "/" + listener_ + "/" + endpoint_);
    }

    MessageURI& SetURI(const std::string uri) {
        int offset1 = 0;
        int offset2 = 0;
        offset1 = uri.find_first_of("/", offset2);
        if (offset1 == offset2) {
            machine_ = "";
        } else {
            machine_ = uri.substr(offset2, offset1);
        }
        offset2 = offset1 + 1;
        offset1 = uri.find_first_of("/", offset2);
        if (offset1 == offset2) {
            listener_ = "";
        } else {
            listener_ = uri.substr(offset2, offset1 - offset2);
        }
        offset2 = offset1 + 1;
        endpoint_ = uri.substr(offset2, uri.size() - offset2);
        return *this;
    }
private:
    std::string machine_ = "";
    std::string listener_ = "";
    std::string endpoint_ = "";
};

}

#endif
