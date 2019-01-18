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
    ParserJsonObject(const parser::ParserJsonObject&&);
    ~ParserJsonObject();

    bool isAvailable();
    bool hasError();
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
    ParserRet getString(char* cache, unsigned int cache_size, struct timespec* overtime);
    ParserRet getInt(int* cache);
    ParserRet getInt(int* cache, struct timespec* overtime);
    ParserRet getLong(long* cache);
    ParserRet getLong(long* cache, struct timespec* overtime);
    ParserRet getDouble(double* cache);
    ParserRet getDouble(double* cache, struct timespec* overtime);
    ParserRet getBool(bool* cache);
    ParserRet getBool(bool* cache, struct timespec* overtime);
    ParserRet getArray(std::vector<ParserJsonObject>* cache);
    ParserRet getArray(std::vector<ParserJsonObject>* cache, struct timespec* overtime);
    ParserRet getObject(std::map<std::string, ParserJsonObject>* cache);
    ParserRet getObject(std::map<std::string, ParserJsonObject>* cache, struct timespec* overtime);

    ParserJsonObject& setString(char* cache, unsigned int cache_size);
    ParserJsonObject& setString(char* cache, unsigned int cache_size, struct timespec* overtime);
    ParserJsonObject& setInt(int cache);
    ParserJsonObject& setInt(int cache, struct timespec* overtime);
    ParserJsonObject& setLong(long cache);
    ParserJsonObject& setLong(long cache, struct timespec* overtime);
    ParserJsonObject& setDouble(double cache);
    ParserJsonObject& setDouble(double cache, struct timespec* overtime);
    ParserJsonObject& setNull();
    ParserJsonObject& setNull(struct timespec* overtime);
    ParserJsonObject& setBool(bool cache);
    ParserJsonObject& setBool(bool cache, struct timespec* overtime);
    ParserJsonObject& setArray();
    ParserJsonObject& setArray(struct timespec* overtime);
    ParserJsonObject& setObject();
    ParserJsonObject& setObject(struct timespec* overtime);

    ParserRet arraySize(unsigned int* size);
    ParserJsonObject& arrayPush(const char* value);
    ParserJsonObject& arrayPush(const char* value, struct timespec* overtime);
    ParserJsonObject& arrayPush(const char* value, unsigned int len);
    ParserJsonObject& arrayPush(const char* value, unsigned int len, struct timespec* overtime);
    ParserJsonObject& arrayPush(int value);
    ParserJsonObject& arrayPush(int value, struct timespec* overtime);
    ParserJsonObject& arrayPush(long value);
    ParserJsonObject& arrayPush(long value, struct timespec* overtime);
    ParserJsonObject& arrayPush(double value);
    ParserJsonObject& arrayPush(double value, struct timespec* overtime);
    ParserJsonObject& arrayPush(bool value);
    ParserJsonObject& arrayPush(bool value, struct timespec* overtime);
    ParserJsonObject& arrayPush(JsonType type, unsigned int size);
    ParserJsonObject& arrayPush(JsonType type, unsigned int size,  struct timespec* overtime);
    ParserJsonObject& arrayPush(ParserJsonObject&& jsontree);
    ParserJsonObject& arrayPush(ParserJsonObject& jsontree);
    ParserJsonObject& arrayPush(ParserJsonObject&& jsontree, struct timespec* overtime);
    ParserJsonObject& arrayPush(ParserJsonObject& jsontree, struct timespec* overtime);

    ParserJsonObject& arrayPop();
    ParserJsonObject& arrayPop(struct timespec* overtime);
    ParserJsonObject& arrayClear();
    ParserJsonObject& arrayClear(struct timespec* overtime);

    bool hasObject(const char* key);
    ParserRet objectSize(unsigned int* size);
    ParserJsonObject& objectAdd(const char* key, const char* value);
    ParserJsonObject& objectAdd(const char* key, const char* value, struct timespec* overtime);
    ParserJsonObject& objectAdd(const char* key, const char* value, unsigned int len);
    ParserJsonObject& objectAdd(const char* key, const char* value, unsigned int len, struct timespec* overtime);
    ParserJsonObject& objectAdd(const char* key, int value);
    ParserJsonObject& objectAdd(const char* key, int value, struct timespec* overtime);
    ParserJsonObject& objectAdd(const char* key, long value);
    ParserJsonObject& objectAdd(const char* key, long value, struct timespec* overtime);
    ParserJsonObject& objectAdd(const char* key, double value);
    ParserJsonObject& objectAdd(const char* key, double value, struct timespec* overtime);
    ParserJsonObject& objectAdd(const char* key, bool value);
    ParserJsonObject& objectAdd(const char* key, bool value, struct timespec* overtime);
    ParserJsonObject& objectAdd(const char* key, JsonType type);
    ParserJsonObject& objectAdd(const char* key, JsonType type, struct timespec* overtime);
    ParserJsonObject& objectAdd(const char* key, ParserJsonObject&& jsontree);
    ParserJsonObject& objectAdd(const char* key, ParserJsonObject& jsontree);
    ParserJsonObject& objectAdd(const char* key, ParserJsonObject&& jsontree, struct timespec* overtime);
    ParserJsonObject& objectAdd(const char* key, ParserJsonObject& jsontree, struct timespec* overtime);

    ParserJsonObject& objectDel(const char* key);
    ParserJsonObject& objectDel(const char* key, struct timespec* overtime);
    ParserJsonObject& objectClear();
    ParserJsonObject& objectClear(struct timespec* overtime);

    ParserJsonObject& Vfind(const char* path);
    ParserJsonObject& Hfind(const char* path);

    ParserJsonObject operator[](int index);
    ParserJsonObject operator[](const char* name);
    ParserJsonObject& operator=(const ParserJsonObject& other);
    ParserJsonObject& operator=(const ParserJsonObject&& other);
private:
    bool init_flag_;
    rapidjson::Value* rpj_value_;
    ParserJson* pj_center_;
    ParserRet last_ret_;

private:
    void _setret(ParserRet ret) {
        this->last_ret_ = ret;
    }
};

class ParserJson {
public:
    friend class ParserJsonObject;

public:
    ParserJsonObject root;

public:
    ParserJson();
    ~ParserJson();

    ParserRet ParserJsonFile(const char* filename);
    ParserRet ParserJsonString(const char* jsonstring);
    ParserRet StorageJsonFile(const char* filename);
    ParserRet StorageJsonString(const char* jsonstring, unsigned int len);

    void setThreadSafe();
    void UnsetThreadSafe();

    ParserRet RLock();
    ParserRet RLock(struct timespec* overtime);
    ParserRet WLock();
    ParserRet WLock(struct timespec* overtime);
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
