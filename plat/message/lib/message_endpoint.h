#ifndef __MESSAGE_ENDPOINT_H__
#define __MESSAGE_ENDPOINT_H__

#include "thread_id.h"

#include "message_return.h"

#define MESSAGE_EP_NAME_MAXLEN (128 + 1)

namespace message {

class MessageEndpoint {
public:
    typedef struct _MessageEndpointInfo {
        char name[MESSAGE_EP_NAME_MAXLEN];
        thread::ThreadID tid;
        //cond
    } MessageEndpointInfo;
public:
    MessageEndpoint(std::string name);
    ~MessageEndpoint();

    MessageRet Search();
private:
    MessageEndpointInfo ep_info_;
};

}

#endif

