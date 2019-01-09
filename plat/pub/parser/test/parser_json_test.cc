#include "parser_json.h"
#include <vector>
#include <map>


int main()
{

    parser::ParserJson pj;
    pj.ParserJsonFile("/home/ezgaoro/workspace/cppfram/etc/pm.json");
    char data[200];
    int idata;
    memset(data, 0x00, sizeof(data));
    //pj.getString("/order/0/name", data, 200);
    pj.find("/order/1").Vfind("/name").getString(data, 200);
    printf("%s\n", data);
    pj.find("/order/0").Vfind("/name").getString(data, 200);
    printf("%s\n", data);
    printf("---------------\n");
    std::vector<parser::ParserJsonObject> v;
    pj.find("/order").getArray(&v);
    for (auto& obj : v) {
        std::map<std::string, parser::ParserJsonObject> m;
        obj.getObject(&m);
        m["name"].getString(data, 200);
        printf("%s\n", data);
        obj.Vfind("/overtime").getInt(&idata);
        printf("%d\n", idata);
    }
    printf("---------------\n");
    pj.find("/order")[0]["name"].getString(data, 200);
    printf("%s\n", data);

    return 0;
}
