#include "message_heartbeat.h"

namespace message {

MessageHeartbeat::MessageHeartbeat()
{

}

MessageHeartbeat::~MessageHeartbeat()
{

}

MessageRet MessageHeartbeat::Add(MessageHeartbeat::Element& element)
{
    return MessageRet::SUCCESS;
}

MessageRet MessageHeartbeat::Del(MessageURI uri)
{
    return MessageRet::SUCCESS;
}

MessageRet MessageHeartbeat::_select_listener_thread_handler(MessageHeartbeat* instance)
{
    return MessageRet::SUCCESS;
}

}
