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
    pj.StoreString(jsonstr);
    printf("%s\n",jsonstr.c_str());
    message::MessageReqConnect msgreqcon2;
    msgreqcon2.Deserialization(pj);

    return 0;
}
