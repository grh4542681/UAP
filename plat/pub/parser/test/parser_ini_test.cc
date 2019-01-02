#include "parser_ini.h"

int main()
{
    parser::ParserIni pi("test.ini");
    pi.Load();
    printf("%ld ---   \n", pi.conftree_.size());
    printf("%ld ---   \n", pi.conftree_.size());
    std::string a = pi.getConfig("s9m24", "RemoteBoxIP");
    printf("%s\n", a.c_str());
    pi.Storage("test_output.ini");
    pi.Free();
    printf("%ld ---   \n", pi.conftree_.size());
    return 0;
}
