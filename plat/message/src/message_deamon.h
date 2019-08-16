#ifndef __MESSAGE_DEAMON_H__
#define __MESSAGE_DEAMON_H__

#include <map>

#include "parser_json.h"

#include "message_return.h"
#include "message_agent.h"

namespace message {

class MessageDeamon {
public:
    MessageDeamon();
    ~MessageDeamon();

    MessageRet Run();
private:
    mempool::MemPool* mempool_;

    std::map<std::string, MessageAgent::MessageAgentInfo*> cep_map_;

    MessageRet _run();
    MessageRet _listen_thread();

};

}

#endif
