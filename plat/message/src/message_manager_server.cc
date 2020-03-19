#include "message_manager_server.h"
#include <unistd.h>

namespace message {

MessageManagerServer::MessageManagerServer() : thread::ThreadRunable() {

}

MessageManagerServer::~MessageManagerServer() {

}

thread::ThreadRet MessageManagerServer::Main() {
    MessageRet ret = _message_manager_server_handler();
    if (ret != MessageRet::SUCCESS) {
        return thread::ThreadRet::ERROR;
    } else {
        return thread::ThreadRet::SUCCESS;
    }
}

MessageRet MessageManagerServer::_message_manager_server_handler() {
    MESSAGE_INFO("Message manager server starting..");
    sleep(100);
    MESSAGE_INFO("Message manager server shutdown..");
    return MessageRet::SUCCESS;
}

}
