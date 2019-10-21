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
    int tmp_int = 0;
    bool tmp_bool = false;

    auto yaml_root = parser.GetDoc();

    // process config
    auto yaml_process = yaml_root.Find("process");
    if (yaml_root.HasError()) {
        PROCESS_FATAL("Not found config : process");
        return config::ConfigRet::ERROR;
    }
    auto config_process = config_tree_.GetRoot()->Insert("process");

    //process pool
    auto yaml_process_pool = yaml_process.Find("pool");
    if (yaml_process.HasError()) {
        PROCESS_FATAL("Not found config : process/pool");
        return config::ConfigRet::ERROR;
    }
    auto config_process_pool = config_process->Insert("pool");

    if (yaml_process_pool.Find("switch").GetData<bool>(&tmp_bool) != parser::ParserRet::SUCCESS) {
        PROCESS_FATAL("Not found config : process/pool/switch");
        return config::ConfigRet::ERROR;
    }
    config_process_pool->Insert<bool>("switch", tmp_bool);
    if (tmp_bool) {
        if (yaml_process_pool.Find("minsize").GetData<int>(&tmp_int) != parser::ParserRet::SUCCESS) {
            PROCESS_FATAL("Not found config : process/pool/minsize");
            return config::ConfigRet::ERROR;
        }
        config_process_pool->Insert<int>("minsize", tmp_int);

        if (yaml_process_pool.Find("maxsize").GetData<int>(&tmp_int) != parser::ParserRet::SUCCESS) {
            PROCESS_FATAL("Not found config : process/pool/maxsize");
            return config::ConfigRet::ERROR;
        }
        config_process_pool->Insert<int>("maxsize", tmp_int);
    }

    // message agent
    auto yaml_process_message =  yaml_process.Find("message");
    if (yaml_root.HasError()) {
        PROCESS_ERROR("Not found config : process/message");
        return config::ConfigRet::ERROR;
    }
    auto config_process_message = config_process->Insert("message");

    if (yaml_process_message.Find("switch").GetData<bool>(&tmp_bool) != parser::ParserRet::SUCCESS) {
        PROCESS_FATAL("Not found config : process/message/switch");
        return config::ConfigRet::ERROR;
    }
    config_process_message->Insert<bool>("switch", tmp_bool);
    if (tmp_bool) {
        if (yaml_process_message.Find("name").GetData<std::string>(&tmp_string) != parser::ParserRet::SUCCESS) {
            PROCESS_FATAL("Not found config : process/message/name");
            return config::ConfigRet::ERROR;
        }
        config_process_message->Insert<std::string>("name", tmp_string);

        if (yaml_process_message.Find("address").GetData<std::string>(&tmp_string) != parser::ParserRet::SUCCESS) {
            PROCESS_FATAL("Not found config : process/message/address");
            return config::ConfigRet::ERROR;
        }
        config_process_message->Insert<std::string>("address", tmp_string);

        if (yaml_process_message.Find("linksize").GetData<int>(&tmp_int) != parser::ParserRet::SUCCESS) {
            PROCESS_FATAL("Not found config : process/message/linksize");
            return config::ConfigRet::ERROR;
        }
        config_process_message->Insert<int>("linksize", tmp_int);
    }

    config_tree_.Print();

    return config::ConfigRet::SUCCESS;
}

}
