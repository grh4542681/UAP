#ifndef __CONFIG_STATIC_H__
#define __CONFIG_STATIC_H__

#include <string>

#include "file.h"
#include "node_tree.h"
#include "parser_ini.h"
#include "parser_json.h"

#include "config_log.h"
#include "config_return.h"

namespace config {

class ConfigStatic {
public:
    ConfigStatic() : config_tree_("config") { };
    ~ConfigStatic() { }

    template < typename T > ConfigRet Load(std::string& str) {
        T parser;
        parser.LoadString(str);
        return Load(parser);
    }
    template < typename T > ConfigRet Load(file::File& file) {
        T parser;
        parser.LoadFile(file);
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

    auto GetRoot();

protected:
    container::NodeTree config_tree_;
    
};

template <> ConfigRet ConfigStatic::Load<parser::ParserJson>(parser::ParserJson& parser);
template <> ConfigRet ConfigStatic::Load<parser::ParserIni>(parser::ParserIni& parser);

}

#endif
