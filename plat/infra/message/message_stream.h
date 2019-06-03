#ifndef __MESSAGE_STREAM_H__
#define __MESSAGE_STREAM_H__

#include <sstream>

namespace message {

class MessageStreamBinary {
public:
    MessageStreamBinary();
    ~MessageStreamBinary();

    template < typename T >
    MessageStreamBinary& Push(T* data);

private:
    std::stringstream ss;

};

}

#endif
