#ifndef __PERSER_JSON_H__
#define __PERSER_JSON_H__

#include <list>
#include <vector>
#include <time.h>

#include "parser_return.h"
#include "mempool.h"
#include "thread_rw_lock.h"
#include "rapidjson/document.h"
#include "rapidjson/pointer.h"

#define MAXJSONFILESIZE (1024*1024)

namespace parser {

class ParserJson;
class ParserJsonObject {
public:
    ParserJsonObject();
    ParserJsonObject(ParserJson*, rapidjson::Value*);
    ~ParserJsonObject();

    bool isString();
    bool isInt();
    bool isDouble();
    bool isNull();
    bool isBool();
    bool isVector();
    bool isStruct();
    
    ParserRet getString(char* cache, unsigned int cache_size);
    ParserRet getString(char* cache, unsigned int cache_size, struct timespec*);
    ParserRet getInt(int* cache);
    ParserRet getInt(int* cache, struct timespec*);
    ParserRet getDouble(double* cache);
    ParserRet getDouble(double* cache, struct timespec*);
    ParserRet getBool(bool* cache);
    ParserRet getBool(bool* cache, struct timespec*);
    ParserRet getVector(std::vector<ParserJsonObject>* cache);
    ParserRet getVector(std::vector<ParserJsonObject>* cache, struct timespec*);
    ParserRet getStruct();

    ParserRet set();

    ParserJsonObject& Vfind(const char* path);
    ParserJsonObject& Hfind(const char* path);
private:
    bool init_flag_;
    rapidjson::Value* rpj_value_;
    ParserJson* pj_center_;
};

class ParserJson {
public:
    ParserJson();
    ~ParserJson();

    ParserRet ParserJsonFile(const char* filename);
    ParserRet ParserJsonString(const char* jsonstring);

    ParserRet RLock();
    ParserRet RLock(struct timespec*);
    ParserRet WLock();
    ParserRet WLock(struct timespec*);
    ParserRet UnLock();

    ParserJsonObject find(const char* path);
private:
    bool init_flag_;
    pub::MemPool* mempool_;
    thread::ThreadRWLock rwlock_;

    rapidjson::Document doc_;
};

}//namespace parser end

#endif
