#ifndef __MESSAGE_STREAM_H__
#define __MESSAGE_STREAM_H__

#include <sstream>

namespace message {

class MessageStreamBinary {
public:
    MessageStreamBinary() {
        ss = std::stringstream(ios_base::in|ios_base::out|ios_base::binary);
    }
    ~MessageStreamBinary() {

    }

    template < typename T >
    MessageStreamBinary& Push(T data) {
        ss << data;
    }

    template < typename T >
    MessageStreamBinary& Pop(T data) {

    }

private:
    std::stringstream ss;

};

}

#endif
