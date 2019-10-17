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
config::ConfigRet ProcessConfig::LoadYaml(parser::ParserYaml& parser)
{
    printf("process config load\n");

    std::string tmp_string;
    int tmp_int;

    auto yaml_root = parser.GetDoc();

    // message config
    auto yaml_message =  yaml_root.Find("message");
    if (yaml_root.HasError()) {
        PROCESS_ERROR("Not found config : message");
        return config::ConfigRet::ERROR;
    }
    auto config_message = config_tree_.GetRoot()->Insert("message");

    // message - name
    auto yaml_message_name = yaml_message.Find("name");
    if (yaml_message.HasError()) {
        PROCESS_ERROR("Not found config : name");
        return config::ConfigRet::ERROR;
    }
    tmp_string.clear();
    yaml_message_name.GetData<std::string>(&tmp_string);
    config_message->Insert<std::string>("name", tmp_string);
    printf("--------%s\n",tmp_string.c_str());

    // message - sockfile
    auto yaml_message_sockfile = yaml_message.Find("sockfile");
    if (yaml_message.HasError()) {
        PROCESS_ERROR("Not found config : sockfile");
        return config::ConfigRet::ERROR;
    }
    tmp_string.clear();
    yaml_message_sockfile.GetData<std::string>(&tmp_string);
    config_message->Insert<std::string>("sockfile", tmp_string);
    printf("--------%s\n",tmp_string.c_str());

    // message - linster_size
    auto yaml_message_linster_size = yaml_message.Find("listener_size");
    if (yaml_message.HasError()) {
        PROCESS_ERROR("Not found config : listener_size");
        return config::ConfigRet::ERROR;
    }
    tmp_int = 0;
    yaml_message_linster_size.GetData<int>(&tmp_int);
    config_message->Insert<int>("linster_size", tmp_int);
    printf("--------%d\n",tmp_int);

    config_tree_.Print();

    return config::ConfigRet::SUCCESS;
}

}
