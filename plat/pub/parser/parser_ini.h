#ifndef __PARSER_INI_H__
#define __PARSER_INI_H__

#include <map>

#include "parser_return.h"
#include "rm_mempool.h"

namespace parser {

class ParserIni{
public:
    typedef std::map<std::string, char*> Section;

    ParserIni(std::string filename);
    ~ParserIni();

    ParserRet Load();
    ParserRet Reload();
    ParserRet Storage(std::string filename);
    ParserRet Free();
    ParserRet Print();

    String getConfig(std::string section, std::string item);
    ParserRet setConfig(std::string section, std::string item, std::string value);

private:
    bool init_flag_;
    rm::RMMemPool* mempool_;
    std::string filename_;
    std::map<std::string, Section*> conftree_;

    ParserRet _load();
    ParserRet _free();
};

}//namespace parser end

#endif
