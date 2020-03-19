#ifndef __CONFIG_STATIC_H__
#define __CONFIG_STATIC_H__

#include <string>

#include "file.h"
#include "node_tree.h"
#include "parser_ini.h"
#include "parser_json.h"
#include "parser_yaml.h"

#include "config_log.h"
#include "config_return.h"

namespace config {

class ConfigStatic {
public:
    ConfigStatic() : config_tree_("config") { };
    ~ConfigStatic() { }

    ConfigRet LoadFile(std::string filename);

    template < typename T > ConfigRet Load(std::string& str) {
        T parser;
        parser.LoadString(str);
        config_filename_.clear();
        return Load(parser);
    }
    template < typename T > ConfigRet Load(file::File& file) {
        T parser;
        parser.LoadFile(file);
        config_filename_ = file.GetFileName();
        return Load(parser);
    }
    template < typename T > ConfigRet Load(T& parser) {
        CONFIG_ERROR("Unsupport parser type %s", typeid(T).name());
        return ConfigRet::CONFIG_EPARSER;
    }

    virtual ConfigRet LoadJson(parser::ParserJson& parser) {
        CONFIG_ERROR("Not support json format config file.");
        return ConfigRet::ESUBCLASS;
    }

    virtual ConfigRet LoadIni(parser::ParserIni& parser) {
        CONFIG_ERROR("Not support ini format config file.");
        return ConfigRet::ESUBCLASS;
    }

    virtual ConfigRet LoadYaml(parser::ParserYaml& parser) {
        CONFIG_ERROR("Not support YAML format config file.");
        return ConfigRet::ESUBCLASS;
    }

    std::string GetConfigFileName();
    container::NodeTree::ElementPath* GetRoot();
    void Print();

protected:
    std::string config_filename_ = "";
    container::NodeTree config_tree_;
    
};

template <> ConfigRet ConfigStatic::Load<parser::Parser>(parser::Parser& parser);
template <> ConfigRet ConfigStatic::Load<parser::ParserJson>(parser::ParserJson& parser);
template <> ConfigRet ConfigStatic::Load<parser::ParserIni>(parser::ParserIni& parser);
template <> ConfigRet ConfigStatic::Load<parser::ParserYaml>(parser::ParserYaml& parser);

}

#endif
