#include "parser_yaml.h"

int main() {

    parser::ParserYaml p;
    p.LoadFile("/home/ezgaoro/workspace/cppfram/plat/etc/process/messaged.yaml");
    auto obj = p.GetDoc().Find("/message/name");
    std::string name;
    obj.GetData<std::string>(&name);
    printf("name - %s\n", name.c_str());

    return 0;
}
