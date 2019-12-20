#include "message_head.h"
#include "message_tag.h"

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

    printf("----------message head test-----------\n");
    message::MessageHead head;
    head.SetMessageBodyFormat(message::MessageFormat::Json);
    head.SetMessageBodyLen(100);

    parser::ParserJson parser;
    head.Serialization(parser);
    std::string str;
    parser.StoreString(str);

    printf("%s\n", str.c_str());

    return 0;
}
