#ifndef __MESSAGE_DEAMON_H__
#define __MESSAGE_DEAMON_H__

#include "message_return.h"

namespace message {

class MessageDeamon {
public:
    MessageDeamon();
    ~MessageDeamon();

    MessageRet Run();
private:
    MessageRet _run();
};

}

#endif
