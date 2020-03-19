#include "message_log.h"
#include "message_manager_server_config.h"

namespace message {

config::ConfigRet MessageManagerServerConfig::LoadJson(parser::ParserJson& parser)
{
    return config::ConfigRet::SUCCESS;
}

config::ConfigRet MessageManagerServerConfig::LoadYaml(parser::ParserYaml& parser)
{
    std::string tmp_string;
    int tmp_int = 0;
    bool tmp_bool = false;

    auto yaml_root = parser.GetDoc();

    auto yaml_message_manager_server =  yaml_root.Find("message_manager_server");
    if (yaml_root.HasError()) {
        MESSAGE_ERROR("Not found config : message_manager_server");
        return config::ConfigRet::ERROR;
    }
    auto config_message_manager_server = config_tree_.GetRoot()->Insert("message_manager_server");
    auto yaml_server_address =  yaml_message_manager_server.Find("address");
    if (yaml_root.HasError()) {
        MESSAGE_ERROR("Not found config : message_manager_server/address");
        return config::ConfigRet::ERROR;
    }

    return config::ConfigRet::SUCCESS;
}

}
