#ifndef __MESSAGE_MANAGER_SERVER_CONFIG_H__
#define __MESSAGE_MANAGER_SERVER_CONFIG_H__

#include "config_static.h"

namespace message {

class MessageManagerServerConfig {
public:
    MessageManagerServerConfig() { }
    ~MessageManagerServerConfig() { }

    config::ConfigRet LoadJson(parser::ParserJson& parser);
    config::ConfigRet LoadYaml(parser::ParserYaml& parser);
};

}

#endif
