#include "message_raw.h"
#include "message_internal.h"

int main()
{
    printf("----------tag test-----------\n");
    message::MessageTag tag;
    tag.SetFormat(message::MessageFormat::Json);
    tag.SetLength(1234);
    printf("%lx\n", tag.BuildTag());
    printf("%ld\n", tag.BuildTag());
    printf("format %d\n", tag.GetFormat());
    printf("length %d\n", tag.GetLength());

    printf("----------MessageReqConnect--------\n");
    message::MessageReqConnect msgreqcon("LOCAL","LOCAL","LOCAL");
    parser::ParserJson pj;
    msgreqcon.Serialization(pj);
    std::string jsonstr;
    pj.StorageJsonString(jsonstr,true);
    printf("%s\n",jsonstr.c_str());
    pj.LoadString(jsonstr);
    message::MessageReqConnect msgreqcon2;
    msgreqcon2.Deserialization(pj);
    printf("%s\n", msgreqcon2.GetDestURI().GetURI().c_str());

    parser::ParserTvl pt;
    msgreqcon.Serialization(pt);
    std::string tvlstr;
    pt.StoreString(tvlstr);
    printf("tvl: ---%s---\n",tvlstr.c_str());
    pt.LoadString(tvlstr);
    message::MessageReqConnect msgreqcon3;
    msgreqcon3.Deserialization(pt);
    printf("%s\n", msgreqcon3.GetDestURI().GetURI().c_str());
    printf("tvl size %lu\n", pt.GetTvlSize());


    return 0;
}
