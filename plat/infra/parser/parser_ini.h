#ifndef __PARSER_INI_H__
#define __PARSER_INI_H__

#include <map>

#include "parser_return.h"
#include "mempool.h"

namespace parser {

class ParserIni{
public:
    typedef std::map<std::string, std::string> Section;

    ParserIni(std::string filename);
    ~ParserIni();

    ParserRet Load();
    ParserRet Reload(std::string filename);
    ParserRet Storage(std::string filename);
    ParserRet Free();
    ParserRet Print();

    std::string getConfig(std::string section, std::string item);
    ParserRet setConfig(std::string section, std::string item, std::string value);

    std::map<std::string, Section*> conftree_;
private:
    bool init_flag_;
    mempool::MemPool* mempool_;
    std::string filename_;

    ParserRet _load();
    ParserRet _free();
};

}//namespace parser end

#endif
