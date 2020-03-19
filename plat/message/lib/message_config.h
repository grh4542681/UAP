#ifndef __MESSAGE_CONFIG_H__
#define __MESSAGE_CONFIG_H__

#include "config_static.h"

namespace message {

class MessageConfig : public config::ConfigStatic {

public:
    MessageConfig() {

    }
    ~MessageConfig(){

    }

    config::ConfigRet LoadJson(parser::ParserJson& parser);
    config::ConfigRet LoadYaml(parser::ParserYaml& parser);
};

}

#endif
