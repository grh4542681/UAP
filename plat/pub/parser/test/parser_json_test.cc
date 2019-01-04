#include "parser_json.h"


int main()
{

    parser::ParserJson pj;
    pj.ParserJsonFile("/home/ezgaoro/workspace/cppfram/etc/pm.json");
    char data[200];
    memset(data, 0x00, sizeof(data));
    pj.getString("/order/0/name", data, 200);
    printf("%s\n", data);

    return 0;
}
