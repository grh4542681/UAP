#ifndef __PERSER_JSON_H__
#define __PERSER_JSON_H__

#include <list>
#include <vector>

#include "parser_return.h"
#include "mempool.h"
#include "rapidjson/document.h"
#include "rapidjson/pointer.h"

#define MAXJSONFILESIZE (1024*1024)

namespace parser {

class ParserJsonObject {
public:
    friend class ParserJson;
    friend class pub::MemPool;

    void Free();

    bool isString();
    bool isInt();
    bool isDouble();
    bool isVector();
    bool isStruct();
    
    ParserRet getString(char* cache, unsigned int cache_size);
    ParserRet getInt(int* cache);
    ParserRet getDouble(double* cache);
    ParserRet getVector(std::vector<ParserJsonObject*>* cache);
    ParserRet getStruct();

    ParserJsonObject* get(const char* path);
private:
    ParserJsonObject(rapidjson::Document*, rapidjson::Value*);
    ~ParserJsonObject();

    bool free_flag_;
    rapidjson::Value* rpjValue_;
    rapidjson::Document* doc_;
};

class ParserJson {
public:
    ParserJson();
    ~ParserJson();

    ParserRet ParserJsonFile(const char* filename);
    ParserRet ParserJsonString(const char* jsonstring);

    ParserRet getString(const char* path, char* cache, unsigned int cache_size);
    ParserJsonObject* get(const char* path);
private:
    bool init_flag_;
    pub::MemPool* mempool_;
    std::list<ParserJsonObject*> object_list_;

    rapidjson::Document doc_;
};

}//namespace parser end

#endif
