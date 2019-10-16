#include "process_config.h"
#include "process_log.h"

namespace process {

config::ConfigRet ProcessConfig::LoadJson(parser::ParserJson& parser)
{
    printf("process config load\n");
    char json_message_string[1024];
    
    auto json_root = parser.find("/");

    // message config
    auto json_message =  json_root.Vfind("/message");
    if (json_root.hasError()) {
        PROCESS_ERROR("Not found config : message");
        return config::ConfigRet::ERROR;
    }
    auto config_message = config_tree_.GetRoot()->Insert("message");

    // message - name
    auto json_message_name = json_message.Vfind("/name");
    if (json_message.hasError()) {
        PROCESS_ERROR("Not found config : name");
        return config::ConfigRet::ERROR;
    }
    memset(json_message_string, 0, sizeof(json_message_string));
    json_message_name.getString(json_message_string, sizeof(json_message_string));
    config_message->Insert<std::string>("name", json_message_string);

    // message - sockfile
    auto json_message_sockfile = json_message.Vfind("/sockfile");
    if (json_message.hasError()) {
        PROCESS_ERROR("Not found config : sockfile");
        return config::ConfigRet::ERROR;
    }
    memset(json_message_string, 0, sizeof(json_message_string));
    json_message_sockfile.getString(json_message_string, sizeof(json_message_string));
    config_message->Insert<std::string>("sockfile", json_message_string);
    printf("--------%s\n",json_message_string);




    return config::ConfigRet::SUCCESS;
}

}
