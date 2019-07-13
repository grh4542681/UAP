#include "message_deamon.h"

namespace message {

MessageDeamon::MessageDeamon()
{

}

MessageDeamon::~MessageDeamon()
{

}

MessageRet MessageDeamon::Run()
{
    return _run();
}

MessageRet MessageDeamon::_run()
{
    return MessageRet::SUCCESS;
}

}
