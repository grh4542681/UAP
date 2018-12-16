#ifndef __PARSER_INI_H__
#define __PARSER_INI_H__

#include <map>

#include "cm_return.h"
#include "rm_mempool.h"

namespace cm {

typedef std::map<std::string, std::string> Section;

class ParserIni{
public:
    ParserIni(const char* filename);
    ParserIni(std::string filename);
    ~ParserIni();

    CmRet Load();
    CmRet Reload();
    CmRet Free();
    String getConfig(std::string path);
    String getConfig(const char* path);

private:
    bool init_flag_;
    rm::RMMemPool* mempool_;
    std::string filename_;
    std::map<std::string, std::map<std::string, std::string>> conftree_;

    CmRet _load();
    CmRet _free();
};

}//namespace cm end

#endif