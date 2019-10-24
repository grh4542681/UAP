#include "file_api.h"
#include "config_static.h"

namespace config {

container::NodeTree::ElementPath* ConfigStatic::GetRoot()
{
    return config_tree_.GetRoot();
}

std::string ConfigStatic::GetConfigFileName()
{
    return config_filename_;
}

ConfigRet ConfigStatic::LoadFile(std::string filename) {
    config_filename_ = filename;
    if (config_filename_.empty() || !file::IsExist(config_filename_)) {
        CONFIG_ERROR("Con't access process config file [%s].", config_filename_.c_str());
        return ConfigRet::CONFIG_ECONFFILE;
    }

    file::File config_file(config_filename_);
    switch(config_file.GetFileFormat()) {
//        case file::File::Format::Ini:
//            Load<parser::ParserIni>(config_file);
//            break;
        case file::File::Format::Json:
            Load<parser::ParserJson>(config_file);
            break;
        case file::File::Format::Yaml:
            Load<parser::ParserYaml>(config_file);
            break;
        default:
            CONFIG_ERROR("Not support config file format [%s]", file::GetFileExtension(config_filename_).c_str());
            return ConfigRet::CONFIG_ECONFFILEFORMAT;
    }
    return ConfigRet::SUCCESS;
}

void ConfigStatic::Print()
{
    config_tree_.Print();
}

template <> ConfigRet ConfigStatic::Load<parser::ParserJson>(parser::ParserJson& parser)
{
    return LoadJson(parser);
}
template <> ConfigRet ConfigStatic::Load<parser::ParserIni>(parser::ParserIni& parser)
{
    return LoadIni(parser);
}
template <> ConfigRet ConfigStatic::Load<parser::ParserYaml>(parser::ParserYaml& parser)
{
    return LoadYaml(parser);
}


}
