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

    config::ConfigRet ret;
    ret = _load_yaml_process(parser);
    if (ret != config::ConfigRet::SUCCESS) {
        PROCESS_FATAL("Load process config error");
        return ret;
    }

    ret = _load_yaml_message(parser);
    if (ret != config::ConfigRet::SUCCESS) {
        PROCESS_FATAL("Load process config error");
        return ret;
    }

    config_tree_.Print();

    return ret;
}

config::ConfigRet ProcessConfig::_load_yaml_process(parser::ParserYaml& parser)
{
    std::string tmp_string;
    int tmp_int = 0;
    bool tmp_bool = false;

    auto yaml_root = parser.GetDoc();

    auto yaml_process = yaml_root.Find("process");
    if (yaml_root.HasError()) {
        PROCESS_FATAL("Not found config : process");
        return config::ConfigRet::ERROR;
    }
    auto config_process = config_tree_.GetRoot()->Insert("process");

    //process pool
    auto yaml_process_pool = yaml_process.Find("group");
    if (yaml_process.HasError()) {
        PROCESS_FATAL("Not found config : process/group");
        return config::ConfigRet::ERROR;
    }
    auto config_process_pool = config_process->Insert("group");

    if (yaml_process_pool.Find("switch").GetData<bool>(&tmp_bool) != parser::ParserRet::SUCCESS) {
        PROCESS_FATAL("Not found config : process/group/switch");
        return config::ConfigRet::ERROR;
    }
    config_process_pool->Insert<bool>("switch", tmp_bool);
    if (tmp_bool) {
        if (yaml_process_pool.Find("size").GetData<int>(&tmp_int) != parser::ParserRet::SUCCESS) {
            PROCESS_FATAL("Not found config : process/group/size");
            return config::ConfigRet::ERROR;
        }
        config_process_pool->Insert<int>("size", tmp_int);
    }
    return config::ConfigRet::SUCCESS;
}

config::ConfigRet ProcessConfig::_load_yaml_message(parser::ParserYaml& parser)
{
    std::string tmp_string;
    int tmp_int = 0;
    bool tmp_bool = false;

    auto yaml_root = parser.GetDoc();

    auto yaml_process_message =  yaml_root.Find("message");
    if (yaml_root.HasError()) {
        PROCESS_ERROR("Not found config : message");
        return config::ConfigRet::ERROR;
    }
    auto config_process_message = config_tree_.GetRoot()->Insert("message");

    if (yaml_process_message.Find("switch").GetData<bool>(&tmp_bool) != parser::ParserRet::SUCCESS) {
        PROCESS_FATAL("Not found config : message/switch");
        return config::ConfigRet::ERROR;
    }
    config_process_message->Insert<bool>("switch", tmp_bool);
    if (tmp_bool) {
        // message agent
        auto yaml_process_message_agent =  yaml_process_message.Find("agent");
        if (yaml_process_message.HasError()) {
            PROCESS_ERROR("Not found config : message/agent");
            return config::ConfigRet::ERROR;
        }
        auto config_process_message_agent = config_process_message->Insert("agent");

        if (yaml_process_message_agent.Find("name").GetData<std::string>(&tmp_string) != parser::ParserRet::SUCCESS) {
            PROCESS_FATAL("Not found config : message/agent/name");
            return config::ConfigRet::ERROR;
        }
        config_process_message_agent->Insert<std::string>("name", tmp_string);

        auto config_process_message_agent_address = config_process_message_agent->Insert("address");
        if (yaml_process_message_agent.Find("address").Find("protocol").GetData<std::string>(&tmp_string) != parser::ParserRet::SUCCESS) {
            PROCESS_FATAL("Not found config : message/agent/address/protocol");
            return config::ConfigRet::ERROR;
        }
        config_process_message_agent_address->Insert<std::string>("protocol", tmp_string);
        if (yaml_process_message_agent.Find("address").Find("device").GetData<std::string>(&tmp_string) != parser::ParserRet::SUCCESS) {
            PROCESS_FATAL("Not found config : message/agent/address/device");
            return config::ConfigRet::ERROR;
        }
        config_process_message_agent_address->Insert<std::string>("device", tmp_string);

        if (yaml_process_message_agent.Find("linksize").GetData<int>(&tmp_int) != parser::ParserRet::SUCCESS) {
            PROCESS_FATAL("Not found config : message/agent/linksize");
            return config::ConfigRet::ERROR;
        }
        config_process_message_agent->Insert<int>("linksize", tmp_int);

        // message manager
        auto yaml_process_message_manager =  yaml_process_message.Find("manager");
        if (yaml_process_message.HasError()) {
            PROCESS_ERROR("Not found config : message/manager");
            return config::ConfigRet::ERROR;
        }
        auto config_process_message_manager = config_process_message->Insert("manager");
        if (yaml_process_message_manager.Find("switch").GetData<bool>(&tmp_bool) != parser::ParserRet::SUCCESS) {
            PROCESS_FATAL("Not found config : message/manager/switch");
            return config::ConfigRet::ERROR;
        }
        config_process_message_manager->Insert<bool>("switch", tmp_bool);
        if (tmp_bool) {
            auto config_process_message_manager_address = config_process_message_manager->Insert("address");
            if (yaml_process_message_manager.Find("address").Find("protocol").GetData<std::string>(&tmp_string) != parser::ParserRet::SUCCESS) {
                PROCESS_FATAL("Not found config : message/agent/address/protocol");
                return config::ConfigRet::ERROR;
            }
            config_process_message_manager_address->Insert<std::string>("protocol", tmp_string);
            if (yaml_process_message_manager.Find("address").Find("device").GetData<std::string>(&tmp_string) != parser::ParserRet::SUCCESS) {
                PROCESS_FATAL("Not found config : message/agent/address/device");
                return config::ConfigRet::ERROR;
            }
            config_process_message_manager_address->Insert<std::string>("device", tmp_string);
        }
    }
    return config::ConfigRet::SUCCESS;
}

}
