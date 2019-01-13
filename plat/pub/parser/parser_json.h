#ifndef __PERSER_JSON_H__
#define __PERSER_JSON_H__

#include <vector>
#include <map>
#include <time.h>

#include "parser_return.h"
#include "mempool.h"
#include "thread_rw_lock.h"
#include "rapidjson/document.h"
#include "rapidjson/pointer.h"

#define MAXJSONFILESIZE (1024*1024)

namespace parser {

typedef enum class _JsonType : int {
    STRING = 1,
    INT,
    DOUBLE,
    BOOL,
    ARRAY,
    OBJECT,
    ONULL,
}JsonType;

class ParserJson;
class ParserJsonObject {
public:
    ParserJsonObject();
    ParserJsonObject(ParserJson*, rapidjson::Value*);
    ParserJsonObject(const parser::ParserJsonObject&);
    ~ParserJsonObject();

    bool isEmpty();

    bool isString();
    bool isInt();
    bool isDouble();
    bool isNull();
    bool isBool();
    bool isArray();
    bool isStruct();
    
    ParserRet getString(char* cache, unsigned int cache_size);
    ParserRet getString(char* cache, unsigned int cache_size, struct timespec*);
    ParserRet getInt(int* cache);
    ParserRet getInt(int* cache, struct timespec*);
    ParserRet getDouble(double* cache);
    ParserRet getDouble(double* cache, struct timespec*);
    ParserRet getBool(bool* cache);
    ParserRet getBool(bool* cache, struct timespec*);
    ParserRet getArray(std::vector<ParserJsonObject>* cache);
    ParserRet getArray(std::vector<ParserJsonObject>* cache, struct timespec*);
    ParserRet getObject(std::map<std::string, ParserJsonObject>* cache);
    ParserRet getObject(std::map<std::string, ParserJsonObject>* cache, struct timespec*);

    ParserRet setString(char* cache, unsigned int cache_size);
    ParserRet setString(char* cache, unsigned int cache_size, struct timespec*);
    ParserRet setInt(int cache);
    ParserRet setInt(int cache, struct timespec*);
    ParserRet setDouble(double cache);
    ParserRet setDouble(double cache, struct timespec*);
    ParserRet setBool(bool cache);
    ParserRet setBool(bool cache, struct timespec*);
    ParserRet setArray();
    ParserRet setArray(struct timespec*)
    ParserRet setObject();
    ParserRet setObject(struct timespec*);

    ParserJsonObject& arrayAdd(ParserJsonObject&);
    ParserJsonObject& arrayAdd(ParserJsonObject&, struct timespec*);

    ParserJsonObject& arrayDel(ParserJsonObject&);
    ParserJsonObject& arrayDel(ParserJsonObject&, struct timespec*);

    ParserJsonObject& objectAdd(const char* key, const char* value, unsigned int len);
    ParserJsonObject& objectAdd(const char* key, const char* value, unsigned int len, struct timespec*);
    ParserJsonObject& objectAdd(const char* key, int value);
    ParserJsonObject& objectAdd(const char* key, int value, struct timespec*);
    ParserJsonObject& objectAdd(const char* key, double value);
    ParserJsonObject& objectAdd(const char* key, double value, struct timespec*);
    ParserJsonObject& objectAdd(const char* key, bool value);
    ParserJsonObject& objectAdd(const char* key, bool value, struct timespec*);
    ParserJsonObject& objectAdd(const char*, JsonType);
    ParserJsonObject& objectAdd(const char*, JsonType, struct timespec*);
    ParserJsonObject& objectAdd(ParserJsonObject&);
    ParserJsonObject& objectAdd(ParserJsonObject&, struct timespec*);

    ParserJsonObject& objectDel(ParserJsonObject&);
    ParserJsonObject& objectDel(ParserJsonObject&, struct timespec*);

    ParserJsonObject& Vfind(const char* path);
    ParserJsonObject& Hfind(const char* path);

    ParserJsonObject operator[](int index);
    ParserJsonObject operator[](const char* name);
private:
    bool init_flag_;
    rapidjson::Value* rpj_value_;
    rapidjson::Value new_rpj_value_;
    ParserJson* pj_center_;
};

class ParserJson {
public:
    friend class ParserJsonObject;
    ParserJson();
    ~ParserJson();

    ParserRet ParserJsonFile(const char* filename);
    ParserRet ParserJsonString(const char* jsonstring);
    ParserRet StorageJsonFile(const char* filename);
    ParserRet StorageJsonString(const char* jsonstring, unsigned int len);

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
