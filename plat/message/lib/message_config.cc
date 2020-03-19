#include "message_log.h"
#include "message_config.h"

namespace message {

config::ConfigRet MessageConfig::LoadJson(parser::ParserJson& parser)
{
    return config::ConfigRet::SUCCESS;
}

config::ConfigRet MessageConfig::LoadYaml(parser::ParserYaml& parser)
{
    std::string tmp_string;
    int tmp_int = 0;
    bool tmp_bool = false;

    auto yaml_root = parser.GetDoc();

    auto yaml_message =  yaml_root.Find("message");
    if (yaml_root.HasError()) {
        MESSAGE_ERROR("Not found config : message");
        return config::ConfigRet::ERROR;
    }
    auto config_message = config_tree_.GetRoot()->Insert("message");

    if (yaml_message.Find("switch").GetData<bool>(&tmp_bool) != parser::ParserRet::SUCCESS) {
        MESSAGE_FATAL("Not found config : message/switch");
        return config::ConfigRet::ERROR;
    }
    config_message->Insert<bool>("switch", tmp_bool);
    if (tmp_bool) {
        // message agent
        auto yaml_message_agent =  yaml_message.Find("agent");
        if (yaml_message.HasError()) {
            MESSAGE_ERROR("Not found config : message/agent");
            return config::ConfigRet::ERROR;
        }
        auto config_message_agent = config_message->Insert("agent");

        if (yaml_message_agent.Find("name").GetData<std::string>(&tmp_string) != parser::ParserRet::SUCCESS) {
            MESSAGE_FATAL("Not found config : message/agent/name");
            return config::ConfigRet::ERROR;
        }
        config_message_agent->Insert<std::string>("name", tmp_string);

        auto config_message_agent_address = config_message_agent->Insert("address");
        if (yaml_message_agent.Find("address").Find("protocol").GetData<std::string>(&tmp_string) != parser::ParserRet::SUCCESS) {
            MESSAGE_FATAL("Not found config : message/agent/address/protocol");
            return config::ConfigRet::ERROR;
        }
        config_message_agent_address->Insert<std::string>("protocol", tmp_string);
        if (yaml_message_agent.Find("address").Find("device").GetData<std::string>(&tmp_string) != parser::ParserRet::SUCCESS) {
            MESSAGE_FATAL("Not found config : message/agent/address/device");
            return config::ConfigRet::ERROR;
        }
        config_message_agent_address->Insert<std::string>("device", tmp_string);

        if (yaml_message_agent.Find("linksize").GetData<int>(&tmp_int) != parser::ParserRet::SUCCESS) {
            MESSAGE_FATAL("Not found config : message/agent/linksize");
            return config::ConfigRet::ERROR;
        }
        config_message_agent->Insert<int>("linksize", tmp_int);

        // message manager
        auto yaml_message_manager =  yaml_message.Find("manager");
        if (yaml_message.HasError()) {
            MESSAGE_ERROR("Not found config : message/manager");
            return config::ConfigRet::ERROR;
        }
        auto config_message_manager = config_message->Insert("manager");
        if (yaml_message_manager.Find("switch").GetData<bool>(&tmp_bool) != parser::ParserRet::SUCCESS) {
            MESSAGE_FATAL("Not found config : message/manager/switch");
            return config::ConfigRet::ERROR;
        }
        config_message_manager->Insert<bool>("switch", tmp_bool);
        if (tmp_bool) {
            auto config_message_manager_address = config_message_manager->Insert("address");
            if (yaml_message_manager.Find("address").Find("protocol").GetData<std::string>(&tmp_string) != parser::ParserRet::SUCCESS) {
                MESSAGE_FATAL("Not found config : message/agent/address/protocol");
                return config::ConfigRet::ERROR;
            }
            config_message_manager_address->Insert<std::string>("protocol", tmp_string);
            if (yaml_message_manager.Find("address").Find("device").GetData<std::string>(&tmp_string) != parser::ParserRet::SUCCESS) {
                MESSAGE_FATAL("Not found config : message/agent/address/device");
                return config::ConfigRet::ERROR;
            }
            config_message_manager_address->Insert<std::string>("device", tmp_string);
        }
    }
    return config::ConfigRet::SUCCESS;
}

}
