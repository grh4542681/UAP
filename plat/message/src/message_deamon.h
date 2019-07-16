#ifndef __MESSAGE_DEAMON_H__
#define __MESSAGE_DEAMON_H__

#include <map>

#include "parser_json.h"

#include "message_return.h"
#include "message_process_endpoint.h"
#include "message_endpoint.h"

namespace message {

class MessageDeamon {
public:
    MessageDeamon();
    ~MessageDeamon();

    MessageRet Run();
private:
    mempool::MemPool* mempool_;

    std::map<std::string, MessageProcessEndpoint*> pep_map_;
    std::map<MessageProcessEndpoint*, MessageEndpoint*> ep_map_;

    MessageRet _register_self();

    MessageRet _run();
};

}

#endif
