#include "process_config.h"
#include "process_log.h"

namespace process {

config::ConfigRet ProcessConfig::LoadJson(parser::ParserJson& parser)
{
    printf("process config load\n");
    auto json_root = parser.find("/");

    // message config
    auto json_message =  json_root.Vfind("/message");
    if (json_root.hasError()) {
        PROCESS_ERROR("Not found config : message");
        return config::ConfigRet::ERROR;
    }
    auto config_message = config_tree_.GetRoot()->Insert("message");

    auto json_message_name = json_message.Vfind("/name");
    char json_message_name_string[1024];
    memset(json_message_name_string, 0, sizeof(json_message_name_string));
    json_message_name.getString(json_message_name_string, sizeof(json_message_name_string));
    printf("----name %s\n", json_message_name_string);
    config_message->Insert<std::string>("name", json_message_name_string);


    return config::ConfigRet::SUCCESS;
}

}
