#include <utility>
#include "config_static.h"

int main()
{
    config::ConfigStatic conf;
    file::File f("/home/ezgaoro/workspace/cppfram/plat/etc/process/messaged.json");
    conf.Load<parser::ParserJson>(f);
    return 0;
}
