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
    ParserRet getLastRet();

    bool isString();
    bool isInt();
    bool isLong();
    bool isDouble();
    bool isNull();
    bool isBool();
    bool isArray();
    bool isObject();
    
    ParserRet getString(char* cache, unsigned int cache_size);
    ParserRet getString(char* cache, unsigned int cache_size, struct timespec*);
    ParserRet getInt(int* cache);
    ParserRet getInt(int* cache, struct timespec*);
    ParserRet getLong(long* cache);
    ParserRet getLong(long* cache, struct timespec*);
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
    ParserRet setLong(long* cache);
    ParserRet setLong(long* cache, struct timespec*);
    ParserRet setDouble(double cache);
    ParserRet setDouble(double cache, struct timespec*);
    ParserRet setBool(bool cache);
    ParserRet setBool(bool cache, struct timespec*);
    ParserRet setArray();
    ParserRet setArray(struct timespec*);
    ParserRet setObject();
    ParserRet setObject(struct timespec*);

    ParserJsonObject& arrayPush(const char* key, const char* value, unsigned int len);
    ParserJsonObject& arrayPush(const char* key, const char* value, unsigned int len, struct timespec*);
    ParserJsonObject& arrayPush(const char* key, int value);
    ParserJsonObject& arrayPush(const char* key, int value, struct timespec*);
    ParserJsonObject& arrayPush(const char* key, long value);
    ParserJsonObject& arrayPush(const char* key, long value, struct timespec*);
    ParserJsonObject& arrayPush(const char* key, double value);
    ParserJsonObject& arrayPush(const char* key, double value, struct timespec*);
    ParserJsonObject& arrayPush(const char* key, bool value);
    ParserJsonObject& arrayPush(const char* key, bool value, struct timespec*);
    ParserJsonObject& arrayPush(const char*, JsonType);
    ParserJsonObject& arrayPush(const char*, JsonType, struct timespec*);

    ParserJsonObject& arrayPop();
    ParserJsonObject& arrayPop(struct timespec*);

    bool hasObject(const char* key);
    ParserJsonObject& objectAdd(const char* key, const char* value, unsigned int len);
    ParserJsonObject& objectAdd(const char* key, const char* value, unsigned int len, struct timespec*);
    ParserJsonObject& objectAdd(const char* key, int value);
    ParserJsonObject& objectAdd(const char* key, int value, struct timespec*);
    ParserJsonObject& objectAdd(const char* key, long value);
    ParserJsonObject& objectAdd(const char* key, long value, struct timespec*);
    ParserJsonObject& objectAdd(const char* key, double value);
    ParserJsonObject& objectAdd(const char* key, double value, struct timespec*);
    ParserJsonObject& objectAdd(const char* key, bool value);
    ParserJsonObject& objectAdd(const char* key, bool value, struct timespec*);
    ParserJsonObject& objectAdd(const char*, JsonType);
    ParserJsonObject& objectAdd(const char*, JsonType, struct timespec*);
    ParserJsonObject& objectAdd(ParserJson&);
    ParserJsonObject& objectAdd(ParserJson&, struct timespec*);

    ParserJsonObject& objectDel(const char* key);
    ParserJsonObject& objectDel(const char* key, struct timespec*);

    ParserJsonObject& Vfind(const char* path);
    ParserJsonObject& Hfind(const char* path);

    ParserJsonObject operator[](int index);
    ParserJsonObject operator[](const char* name);
private:
    bool init_flag_;
    rapidjson::Value* rpj_value_;
    ParserJson* pj_center_;
    ParserRet last_ret_;

    void _setret(ParserRet ret) {
        this->last_ret_ = ret;
    }
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

    void setThreadSafe();
    void UnsetThreadSafe();

    ParserRet RLock();
    ParserRet RLock(struct timespec*);
    ParserRet WLock();
    ParserRet WLock(struct timespec*);
    ParserRet UnLock();

    ParserJsonObject find(const char* path);
private:
    bool init_flag_;
    bool thread_safe_flag_;
    pub::MemPool* mempool_;
    thread::ThreadRWLock rwlock_;

    rapidjson::Document doc_;
};

}//namespace parser end

#endif
