#ifndef __MESSAGE_MANAGER_SERVER_H__
#define __MESSAGE_MANAGER_SERVER_H__

//#include "thread_template.h"
#include "thread_runable.h"
#include "mutex/thread_rw_lock.h"

#include "message_log.h"
#include "message_return.h"


namespace message {

class MessageManagerServer : public thread::ThreadRunable {
public:
    MessageManagerServer();
    ~MessageManagerServer();

    thread::ThreadRet Main();
private:
    MessageRet _message_manager_server_handler();
//    thread::ThreadTemplate<decltype(&message::MessageManagerServer::_message_manager_server_handler), MessageRet> manager_thread_;
};

}

#endif
