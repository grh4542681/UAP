#include "message_heartbeat.h"

namespace message {

HeartbeatClient::HeartbeatClient()
{

}

HeartbeatClient::~HeartbeatClient()
{

}

MessageRet HeartbeatClient::Add(HeartbeatElement& element)
{
    return MessageRet::SUCCESS;
}

MessageRet HeartbeatClient::Del(MessageURI uri)
{
    return MessageRet::SUCCESS;
}

//MessageRet HeartbeatClient::_select_listener_thread_handler(HeartbeatClient* instance)
//{
//    return MessageRet::SUCCESS;
//}

}
