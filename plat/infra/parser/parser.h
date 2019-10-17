#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include "file.h"

#include "parser_return.h"

namespace parser {

class Parser {
public:
    Parser() { };
    virtual ~Parser() { };

    virtual ParserRet LoadString(std::string str) = 0;
    virtual ParserRet LoadFile(file::File& file) = 0;
    virtual ParserRet LoadFile(std::string str) = 0;
};

}

#endif
