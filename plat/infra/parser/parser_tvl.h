#ifndef __PARSER_TVL_H__
#define __PARSER_TVL_H__

#include "parser.h"

namespace parser {

class ParserTvl : public Parser {
public:
    ParserTvl();
    ~ParserTvl();

    ParserRet LoadString(std::string str);
    ParserRet LoadFile(file::File& file);
    ParserRet LoadFile(std::string str);
    
    ParserRet StoreString(std::string& str);
    ParserRet StoreFile(file::File& file);
    ParserRet StoreFile(std::string str);
private:

};

}

#endif
