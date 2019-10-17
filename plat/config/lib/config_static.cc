#include "config_static.h"

namespace config {

container::NodeTree::ElementPath* ConfigStatic::GetRoot()
{
    return config_tree_.GetRoot();
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
