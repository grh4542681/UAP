#ifndef __MESSAGE_ENDPOINT_H__
#define __MESSAGE_ENDPOINT_H__

#include "thread_id.h"

#include "message_return.h"
#include "message_defines.h"

namespace message {
class MessageListener;
class MessageEndpoint {
public:
    typedef struct _MessageEndpointInfo {
        char name[MESSAGE_ENDPOINT_NAME_MAX_LEN] = { 0 };
        char listener_name[MESSAGE_ENDPOINT_NAME_MAX_LEN] = { 0 };
        thread::ThreadID tid;
        //cond
    } MessageEndpointInfo;
public:
    MessageEndpoint(std::string name);
    ~MessageEndpoint();

    MessageRet Register();
    MessageRet Unregister();

private:
    MessageListener* listener;
    MessageEndpointInfo ep_info_;
};

}

#endif

