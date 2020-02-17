#ifndef __MESSAGE_ENDPOINT_H__
#define __MESSAGE_ENDPOINT_H__

#include <string>
#include <list>
#include <functional>

#include "thread_id.h"

#include "message_return.h"
#include "message_defines.h"

namespace message {
class MessageListener;
class MessageEndpoint {
public:
    enum class State {
        Initialize,
        Ready,
        Listening,
        Error,
    };

    typedef struct _Info {
        char name[MESSAGE_ENDPOINT_NAME_MAX_LEN] = { 0 };
        char listener_name[MESSAGE_ENDPOINT_NAME_MAX_LEN] = { 0 };
        thread::ThreadID tid;
        //cond
    } Info;

public:
    MessageEndpoint(std::string name);
    ~MessageEndpoint();

    MessageRet Register();
    MessageRet Unregister();

private:
    MessageListener* listener;
    Info info_;

//    thread::mutex::ThreadCondLock request_queue_cond_;
    std::list<std::string> request_queue_;
//    thread::mutex::ThreadCondLock reponse_queue_cond_;
    std::list<std::string> reponse_queue_;
};

}

#endif

