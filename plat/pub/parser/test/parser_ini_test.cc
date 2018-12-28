#include "parser_ini.h"

int main()
{
    parser::ParserIni pi("test.ini");
    pi.Load();
    printf("%d ---   \n", pi.conftree_.size());
    pi.Print();
    printf("%d ---   \n", pi.conftree_.size());
    std::string a = pi.getConfig("s9m24", "RemoteBoxIP");
    printf("%s\n", a.c_str());
    pi.Free();
    printf("%d ---   \n", pi.conftree_.size());
    return 0;
}
