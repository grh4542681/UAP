#include "message_header.h"

int main()
{
    message::MessageHeader header;
    header.SetMessageBodyFormat(message::MessageFormat::Json);
    header.SetMessageBodyLen(100);

    parser::ParserJson parser;
    header.Serialization(parser);
    std::string str;
    parser.StoreString(str);

    printf("%s\n", str.c_str());

    return 0;
}
