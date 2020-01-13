#include "message_heartbeat.h"

namespace message {

MessageHeartbeatClient::MessageHeartbeatClient()
{

}

MessageHeartbeatClient::~MessageHeartbeatClient()
{

}

MessageRet MessageHeartbeatClient::Add(MessageHeartbeatElement& element)
{
    return MessageRet::SUCCESS;
}

MessageRet MessageHeartbeatClient::Del(MessageURI uri)
{
    return MessageRet::SUCCESS;
}

//MessageRet MessageHeartbeatClient::_select_listener_thread_handler(MessageHeartbeatClient* instance)
//{
//    return MessageRet::SUCCESS;
//}

}
