#ifndef __PROCESS_CONFIG_H__
#define __PROCESS_CONFIG_H__

#include "config_static.h"

namespace process {

class ProcessConfig : public config::ConfigStatic {
public:
    ProcessConfig() {

    }
    ~ProcessConfig(){

    }

    config::ConfigRet LoadJson(parser::ParserJson& parser);
    config::ConfigRet LoadYaml(parser::ParserYaml& parser);

private:
    config::ConfigRet _load_yaml_process(parser::ParserYaml& parser);
    config::ConfigRet _load_yaml_message(parser::ParserYaml& parser);

};

}

#endif
