#include <unistd.h>

#include "parser_log.h"
#include "parser_return.h"
#include "parser_json.h"

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/writer.h"

namespace parser {

//ParserJsonObject class
/**
* @brief ParserJsonObject - Default constructor
*/
ParserJsonObject::ParserJsonObject()
{
    this->rpj_value_ = NULL;
    this->pj_center_ = NULL;
    this->init_flag_ = true;
    this->last_ret_ = ParserRet::SUCCESS;
}

/**
* @brief ParserJsonObject - Constructor
*
* @param [pj_center] - The json parser center
* @param [rpj_value] - The json object(rapidjson)
*/
ParserJsonObject::ParserJsonObject(ParserJson* pj_center, rapidjson::Value* rpj_value)
{
    this->rpj_value_ = rpj_value;
    this->pj_center_ = pj_center;
    this->last_ret_ = ParserRet::SUCCESS;
    if (!rpj_value || !pj_center) {
        this->init_flag_ = false;
    } else {
        this->init_flag_ = true;
    }
}

/**
* @brief ParserJsonObject - Copy constructot
*
* @param [old] - source object
*/
ParserJsonObject::ParserJsonObject(const parser::ParserJsonObject& old)
{
    this->rpj_value_ = old.rpj_value_;
    this->pj_center_ = old.pj_center_;
    this->init_flag_ = old.init_flag_;
    this->last_ret_ = old.last_ret_;
}

/**
* @brief ~ParserJsonObject - Destructor
*/
ParserJsonObject::~ParserJsonObject()
{

}

/**
* @brief isEmpty - Determine if the object is available
*
* @returns  bool
*/
bool ParserJsonObject::isEmpty()
{
    return this->init_flag_;
}

/**
* @brief getLastRet - Get last return value. Some function did not use the return 
*                     value to indicate an error, it will update a global return 
*                     value.
*
* @returns  ParserRet.
*/
ParserRet ParserJsonObject::getLastRet()
{
    return this->last_ret_;
}

/**
* @brief isString - Determine if the value of the current object is a string
*
* @returns  bool
*/
bool ParserJsonObject::isString()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return false;
    }
    _setret(ParserRet::SUCCESS);
    return this->rpj_value_->IsString();
}

/**
* @brief isInt - Determine if the value of the current object is a int
*
* @returns bool 
*/
bool ParserJsonObject::isInt()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return false;
    }
    _setret(ParserRet::SUCCESS);
    return this->rpj_value_->IsInt();
}

bool ParserJsonObject::isLong()
{

}

/**
* @brief isDouble - Determine if the value of the current object is a double
*
* @returns  bool
*/
bool ParserJsonObject::isDouble()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return false;
    }
    _setret(ParserRet::SUCCESS);
    return this->rpj_value_->IsDouble();
}

/**
* @brief isNull - Determine if the value of the current object is a null
*
* @returns  bool
*/
bool ParserJsonObject::isNull()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return false;
    }
    _setret(ParserRet::SUCCESS);
    return this->rpj_value_->IsNull();
}

/**
* @brief isBool - Determine if the value of the current object is a bool
*
* @returns  bool
*/
bool ParserJsonObject::isBool()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return false;
    }
    _setret(ParserRet::SUCCESS);
    return this->rpj_value_->IsBool();
}

/**
* @brief isArray - Determine if the value of the current object is a array
*
* @returns  bool
*/
bool ParserJsonObject::isArray()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return false;
    }
    _setret(ParserRet::SUCCESS);
    return this->rpj_value_->IsArray();
}

/**
* @brief isObject - Determine if the value of the current object is a object
*
* @returns  bool
*/
bool ParserJsonObject::isObject()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return false;
    }
    _setret(ParserRet::SUCCESS);
    return this->rpj_value_->IsObject();
}

bool ParserJsonObject::isStruct()
{

}
    
/**
* @brief getString - If the current object is of type string, then get its value
*                    If cache is small than value it will return error
*
* @param [cache] - Cache address
* @param [cache_size] - Cache size
*
* @returns  ParserRet
*/
ParserRet ParserJsonObject::getString(char* cache, unsigned int cache_size)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserRet::EINIT;
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ret;
    }
    if (this->rpj_value_->IsString()) {
        if (cache_size > this->rpj_value_->GetStringLength()) {
            memcpy(cache, this->rpj_value_->GetString(), this->rpj_value_->GetStringLength());
            this->pj_center_->UnLock();
            return ParserRet::SUCCESS;
        } else {
            PARSER_ERROR("Cache size is not enough, need at least [%d]",this->rpj_value_->GetStringLength());
            this->pj_center_->UnLock();
            return ParserRet::EBADARGS;
        }
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
}

/**
* @brief getString - If the current object is of type string, then get its value
*                    If cache is small than value it will return error.
*                    This function will block until other thread change this object done.
*
* @param [cache] - Cache address
* @param [cache_size] - Cache size
* @param [overtime] - Over time
*
* @returns  ParserRet
*/
ParserRet ParserJsonObject::getString(char* cache, unsigned int cache_size, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserRet::EINIT;
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ret;
    }
    if (this->rpj_value_->IsString()) {
        if (cache_size > this->rpj_value_->GetStringLength()) {
            memcpy(cache, this->rpj_value_->GetString(), this->rpj_value_->GetStringLength());
            this->pj_center_->UnLock();
            return ParserRet::SUCCESS;
        } else {
            PARSER_ERROR("Cache size is not enough, need at least [%d]",this->rpj_value_->GetStringLength());
            this->pj_center_->UnLock();
            return ParserRet::EBADARGS;
        }
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
}
    
/**
* @brief getInt - If the current object is of type int, then get its value
*
* @param [cache] - Cache address
*
* @returns  ParserRet
*/
ParserRet ParserJsonObject::getInt(int* cache)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserRet::EINIT;
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ret;
    }
    if (this->rpj_value_->IsInt()) {
        *cache = this->rpj_value_->GetInt();
        this->pj_center_->UnLock();
        return ParserRet::SUCCESS;
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
}

/**
* @brief getInt - If the current object is of type int, then get its value.
*                 This function will block until other thread change this object done.
*
* @param [cache] - Cache address
* @param [overtime] - Over time
*
* @returns  ParserRet
*/
ParserRet ParserJsonObject::getInt(int* cache, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserRet::EINIT;
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ret;
    }
    if (this->rpj_value_->IsInt()) {
        *cache = this->rpj_value_->GetInt();
        this->pj_center_->UnLock();
        return ParserRet::SUCCESS;
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
}

ParserRet ParserJsonObject::getLong(long* cache)
{

}

ParserRet ParserJsonObject::getLong(long* cache, struct timespec*)
{

}

/**
* @brief getDouble - If the current object is of type double, then get its value.
*
* @param [cache] - Cache address.
*
* @returns  ParserRet
*/
ParserRet ParserJsonObject::getDouble(double* cache)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserRet::EINIT;
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ret;
    }
    if (this->rpj_value_->IsDouble()) {
        *cache = this->rpj_value_->GetDouble();
        this->pj_center_->UnLock();
        return ParserRet::SUCCESS;
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
}

/**
* @brief getDouble - If the current object is of type double, then get its value.
*                    This function will block until other thread change this object done.
*
* @param [cache] - Cache address.
* @param [overtime] - Over time.
*
* @returns  ParserRet
*/
ParserRet ParserJsonObject::getDouble(double* cache, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserRet::EINIT;
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ret;
    }
    if (this->rpj_value_->IsDouble()) {
        *cache = this->rpj_value_->GetDouble();
        this->pj_center_->UnLock();
        return ParserRet::SUCCESS;
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
}

/**
* @brief getBool - If the current object is of type bool, then get its value.
*
* @param [cache] - Cache address.
*
* @returns  ParserRet.
*/
ParserRet ParserJsonObject::getBool(bool* cache)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserRet::EINIT;
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ret;
    }
    if (this->rpj_value_->IsBool()) {
        *cache = this->rpj_value_->GetBool();
        this->pj_center_->UnLock();
        return ParserRet::SUCCESS;
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
}

/**
* @brief getBool - If the current object is of type bool, then get its value.
*                  This function will block until other thread change this object done.
*
* @param [cache] - Cache address.
* @param [overtime] - Over time.
*
* @returns  ParserRet.
*/
ParserRet ParserJsonObject::getBool(bool* cache, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserRet::EINIT;
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ret;
    }
    if (this->rpj_value_->IsBool()) {
        *cache = this->rpj_value_->GetBool();
        this->pj_center_->UnLock();
        return ParserRet::SUCCESS;
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
}
    
/**
* @brief getArray - If the current object is of type array, then get its value.
*                   This function used vector storage all object in this arry.
*
* @param [cache] - Vector address.
*
* @returns  ParserRet.
*/
ParserRet ParserJsonObject::getArray(std::vector<ParserJsonObject>* cache)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserRet::EINIT;
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ret;
    }
    if (this->rpj_value_->IsArray()) {
        for (auto& a : this->rpj_value_->GetArray()) {
            cache->push_back(ParserJsonObject(this->pj_center_, &a));
        }
        this->pj_center_->UnLock();
        return ParserRet::SUCCESS;
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
}

/**
* @brief getArray - If the current object is of type array, then get its value.
*                   This function used vector storage all object in this arry.
*                   This function will block until other thread change this object done.
*
* @param [cache] - Vector address.
* @param [overtime] - Over time.
*
* @returns  ParserRet.
*/
ParserRet ParserJsonObject::getArray(std::vector<ParserJsonObject>* cache, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserRet::EINIT;
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ret;
    }
    if (this->rpj_value_->IsArray()) {
        for (auto& a : this->rpj_value_->GetArray()) {
            cache->push_back(ParserJsonObject(this->pj_center_, &a));
        }
        this->pj_center_->UnLock();
        return ParserRet::SUCCESS;
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
}

/**
* @brief getObject - If the current object is of type object, then get its value.
*                    This function used map storage all object in under this object, you
*                    can use the object name to get corresponding object from the map.
*
* @param [cache] - Map address.
*
* @returns  ParserRet.
*/
ParserRet ParserJsonObject::getObject(std::map<std::string, ParserJsonObject>* cache)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserRet::EINIT;
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ret;
    }
    if (this->rpj_value_->IsObject()) {
        for (auto& m : this->rpj_value_->GetObject()) {
            cache->insert(std::pair<std::string, ParserJsonObject>(m.name.GetString(), ParserJsonObject(this->pj_center_, &(m.value))));
        }
        this->pj_center_->UnLock();
        return ParserRet::SUCCESS;
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
}

/**
* @brief getObject - If the current object is of type object, then get its value.
*                    This function used map storage all object in under this object, you
*                    can use the object name to get corresponding object from the map.
*                    This function will block until other thread change this object done.
*
* @param [cache] - Map address.
* @param [overtime] - Over time.
*
* @returns  ParserRet.
*/
ParserRet ParserJsonObject::getObject(std::map<std::string, ParserJsonObject>* cache, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserRet::EINIT;
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ret;
    }
    if (this->rpj_value_->IsObject()) {
        for (auto& m : this->rpj_value_->GetObject()) {
            cache->insert(std::pair<std::string, ParserJsonObject>(m.name.GetString(), ParserJsonObject(this->pj_center_, &(m.value))));
        }
        this->pj_center_->UnLock();
        return ParserRet::SUCCESS;
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
}


ParserRet ParserJsonObject::setString(char* cache, unsigned int cache_size)
{

}

ParserRet ParserJsonObject::setString(char* cache, unsigned int cache_size, struct timespec*)
{

}

ParserRet ParserJsonObject::setInt(int cache)
{

}

ParserRet ParserJsonObject::setInt(int cache, struct timespec*)
{

}

ParserRet ParserJsonObject::setLong(long* cache)
{

}

ParserRet ParserJsonObject::setLong(long* cache, struct timespec*)
{

}

ParserRet ParserJsonObject::setDouble(double cache)
{

}

ParserRet ParserJsonObject::setDouble(double cache, struct timespec*)
{

}

ParserRet ParserJsonObject::setBool(bool cache)
{

}

ParserRet ParserJsonObject::setBool(bool cache, struct timespec*)
{

}

ParserRet ParserJsonObject::setArray()
{

}

ParserRet ParserJsonObject::setArray(struct timespec*)
{

}

ParserRet ParserJsonObject::setObject()
{

}

ParserRet ParserJsonObject::setObject(struct timespec*)
{

}

ParserJsonObject& ParserJsonObject::arrayPush(const char* key, const char* value, unsigned int len)
{

}

ParserJsonObject& ParserJsonObject::arrayPush(const char* key, const char* value, unsigned int len, struct timespec*)
{

}

ParserJsonObject& ParserJsonObject::arrayPush(const char* key, int value)
{

}

ParserJsonObject& ParserJsonObject::arrayPush(const char* key, int value, struct timespec*)
{

}

ParserJsonObject& ParserJsonObject::arrayPush(const char* key, long value)
{

}

ParserJsonObject& ParserJsonObject::arrayPush(const char* key, long value, struct timespec*)
{

}

ParserJsonObject& ParserJsonObject::arrayPush(const char* key, double value)
{

}

ParserJsonObject& ParserJsonObject::arrayPush(const char* key, double value, struct timespec*)
{

}

ParserJsonObject& ParserJsonObject::arrayPush(const char* key, bool value)
{

}

ParserJsonObject& ParserJsonObject::arrayPush(const char* key, bool value, struct timespec*)
{

}

ParserJsonObject& ParserJsonObject::arrayPush(const char*, JsonType)
{

}

ParserJsonObject& ParserJsonObject::arrayPush(const char*, JsonType, struct timespec*)
{

}

ParserJsonObject& ParserJsonObject::arrayPop()
{

}

ParserJsonObject& ParserJsonObject::arrayPop(struct timespec*)
{

}



/**
* @brief hasObject - Determine whether the current object has the specified child object.
*
* @param [key] - Object name.
*
* @returns  bool.
*/
bool ParserJsonObject::hasObject(const char* key)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return false;
    }
    if (this->rpj_value_->IsObject()) {
        ParserRet ret;
        if ((ret = this->pj_center_->RLock()) != ParserRet::SUCCESS) {
            PARSER_ERROR("Get read lock error!");
            _setret(ParserRet::EGETRLOCK);
            return false;
        }
        bool hasflag = this->rpj_value_->HasMember(key);
        this->pj_center_->UnLock();
        _setret(ParserRet::SUCCESS);
        return hasflag;
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return false;
    }
}

/**
* @brief objectAdd - If the current object is of type object, then add a child object.
*                    This function add a string object.
*
* @param [key] - Object name.
* @param [value] - String address.
* @param [len] - String len.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::objectAdd(const char* key, const char* value, unsigned int len)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (this->rpj_value_->IsObject()) {
        if (this->pj_center_->WLock() != ParserRet::SUCCESS) {
            PARSER_ERROR("Get write lock error!");
            _setret(ParserRet::EGETWLOCK);
            return *this;
        }
        rapidjson::Value rvalue(value, len, this->pj_center_->doc_.GetAllocator());
        rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
        this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
        this->pj_center_->UnLock();
        _setret(ParserRet::SUCCESS);
        return *this;
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
}

/**
* @brief objectAdd - If the current object is of type object, then add a child object.
*                    This function add a string object.
*                    This function will block until other thread change this object done.
*
* @param [key] - Object name.
* @param [value] - String address.
* @param [len] - String len.
* @param [overtime] - Over time.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::objectAdd(const char* key, const char* value, unsigned int len, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (this->rpj_value_->IsObject()) {
        if (this->pj_center_->WLock(overtime) != ParserRet::SUCCESS) {
            PARSER_ERROR("Get write lock error!");
            _setret(ParserRet::EGETWLOCK);
            return *this;
        }
        rapidjson::Value rvalue(value, len, this->pj_center_->doc_.GetAllocator());
        rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
        this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
        this->pj_center_->UnLock();
        _setret(ParserRet::SUCCESS);
        return *this;
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
}

ParserJsonObject& ParserJsonObject::objectAdd(const char* key, int value)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (this->rpj_value_->IsObject()) {
        if (this->pj_center_->WLock() != ParserRet::SUCCESS) {
            PARSER_ERROR("Get write lock error!");
            _setret(ParserRet::EGETWLOCK);
            return *this;
        }
        rapidjson::Value rvalue(value);
        rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
        this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
        this->pj_center_->UnLock();
        _setret(ParserRet::SUCCESS);
        return *this;
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
}

ParserJsonObject& ParserJsonObject::objectAdd(const char* key, int value, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (this->rpj_value_->IsObject()) {
        if (this->pj_center_->WLock(overtime) != ParserRet::SUCCESS) {
            PARSER_ERROR("Get write lock error!");
            _setret(ParserRet::EGETWLOCK);
            return *this;
        }
        rapidjson::Value rvalue(value);
        rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
        this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
        this->pj_center_->UnLock();
        _setret(ParserRet::SUCCESS);
        return *this;
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
}

ParserJsonObject& objectAdd(const char* key, long value)
{

}

ParserJsonObject& objectAdd(const char* key, long value, struct timespec*)
{

}

ParserJsonObject& ParserJsonObject::objectAdd(const char* key, double value)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (this->rpj_value_->IsObject()) {
        if (this->pj_center_->WLock() != ParserRet::SUCCESS) {
            PARSER_ERROR("Get write lock error!");
            _setret(ParserRet::EGETWLOCK);
            return *this;
        }
        rapidjson::Value rvalue(value);
        rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
        this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
        this->pj_center_->UnLock();
        _setret(ParserRet::SUCCESS);
        return *this;
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
}

ParserJsonObject& ParserJsonObject::objectAdd(const char* key, double value, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (this->rpj_value_->IsObject()) {
        if (this->pj_center_->WLock(overtime) != ParserRet::SUCCESS) {
            PARSER_ERROR("Get write lock error!");
            _setret(ParserRet::EGETWLOCK);
            return *this;
        }
        rapidjson::Value rvalue(value);
        rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
        this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
        this->pj_center_->UnLock();
        _setret(ParserRet::SUCCESS);
        return *this;
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
}

ParserJsonObject& ParserJsonObject::objectAdd(const char* key, bool value)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (this->rpj_value_->IsObject()) {
        if (this->pj_center_->WLock() != ParserRet::SUCCESS) {
            PARSER_ERROR("Get write lock error!");
            _setret(ParserRet::EGETWLOCK);
            return *this;
        }
        rapidjson::Value rvalue(value);
        rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
        this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
        this->pj_center_->UnLock();
        _setret(ParserRet::SUCCESS);
        return *this;
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
}

ParserJsonObject& ParserJsonObject::objectAdd(const char* key, bool value, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (this->rpj_value_->IsObject()) {
        if (this->pj_center_->WLock(overtime) != ParserRet::SUCCESS) {
            PARSER_ERROR("Get write lock error!");
            _setret(ParserRet::EGETWLOCK);
            return *this;
        }
        rapidjson::Value rvalue(value);
        rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
        this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
        this->pj_center_->UnLock();
        _setret(ParserRet::SUCCESS);
        return *this;
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
}

ParserJsonObject& ParserJsonObject::objectAdd(const char* key, JsonType type)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (this->rpj_value_->IsObject()) {
        if (this->pj_center_->WLock() != ParserRet::SUCCESS) {
            PARSER_ERROR("Get write lock error!");
            _setret(ParserRet::EGETWLOCK);
            return *this;
        }
        rapidjson::Type value_type;
        switch (type) {
            case JsonType::ARRAY:
                value_type = rapidjson::Type::kArrayType;
                break;
            case JsonType::OBJECT:
                value_type = rapidjson::Type::kObjectType;
                break;
            case JsonType::ONULL:
                value_type = rapidjson::Type::kNullType;
                break;
            case JsonType::INT:
                value_type = rapidjson::Type::kNumberType;
                break;
            default:
                PARSER_ERROR("Unsupport object type[%d]", static_cast<int>(type));
                _setret(ParserRet::EMAHTYPE);
                return *this;
        }
        rapidjson::Value rvalue(value_type);
        rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
        this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
        this->pj_center_->UnLock();
        _setret(ParserRet::SUCCESS);
        return *this;
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
}

ParserJsonObject& ParserJsonObject::objectAdd(const char* key, JsonType type, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (this->rpj_value_->IsObject()) {
        if (this->pj_center_->WLock(overtime) != ParserRet::SUCCESS) {
            PARSER_ERROR("Get write lock error!");
            _setret(ParserRet::EGETWLOCK);
            return *this;
        }
        rapidjson::Type value_type;
        switch (type) {
            case JsonType::ARRAY:
                value_type = rapidjson::Type::kArrayType;
                break;
            case JsonType::OBJECT:
                value_type = rapidjson::Type::kObjectType;
                break;
            case JsonType::ONULL:
                value_type = rapidjson::Type::kNullType;
                break;
            case JsonType::INT:
                value_type = rapidjson::Type::kNumberType;
                break;
            default:
                PARSER_ERROR("Unsupport object type[%d]", static_cast<int>(type));
                _setret(ParserRet::EMAHTYPE);
                return *this;
        }
        rapidjson::Value rvalue(value_type);
        rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
        this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
        this->pj_center_->UnLock();
        _setret(ParserRet::SUCCESS);
        return *this;
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
}

ParserJsonObject& ParserJsonObject::objectAdd(ParserJson& jsontree)
{

}

ParserJsonObject& ParserJsonObject::objectAdd(ParserJson& jsontree, struct timespec* overtime)
{

}

ParserJsonObject& ParserJsonObject::objectDel(const char* key)
{

}

ParserJsonObject& ParserJsonObject::objectDel(const char* key, struct timespec*)
{

}

ParserJsonObject& ParserJsonObject::Vfind(const char* path)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (rapidjson::Value* data = rapidjson::Pointer(path).Get(*(this->rpj_value_))) {
        this->rpj_value_ = data;
        _setret(ParserRet::SUCCESS);
        return *this;
    } else {
        PARSER_ERROR("Can not find path[%s]", path);
        _setret(ParserRet::ENOTFOUND);
        return *this;
    }
}

ParserJsonObject& ParserJsonObject::Hfind(const char* name)
{
    PARSER_ERROR("Not support");
    return *this;
}

ParserJsonObject ParserJsonObject::operator[](int index)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return ParserJsonObject();
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        _setret(ParserRet::EGETRLOCK);
        return ParserJsonObject();
    }
    if (this->rpj_value_->IsArray()) {
        if (index < 0 || static_cast<unsigned int>(index) > this->rpj_value_->Size()) {
            this->pj_center_->UnLock();
            _setret(ParserRet::EBADARGS);
            return ParserJsonObject();
        } else {
            this->pj_center_->UnLock();
            _setret(ParserRet::SUCCESS);
            return ParserJsonObject(this->pj_center_, &((*(this->rpj_value_))[index]));
        }
    } else {
        this->pj_center_->UnLock();
        _setret(ParserRet::EMAHTYPE);
        return ParserJsonObject();
    }
}

ParserJsonObject ParserJsonObject::operator[](const char* name)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return ParserJsonObject();
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        _setret(ParserRet::EGETRLOCK);
        return ParserJsonObject();
    }
    if (this->rpj_value_->IsObject()) {
        rapidjson::Value::ConstMemberIterator itr = this->rpj_value_->FindMember(name);
        if (itr == this->rpj_value_->MemberEnd()) {
            this->pj_center_->UnLock();
            _setret(ParserRet::ENOTFOUND);
            return ParserJsonObject();
        } else {
            this->pj_center_->UnLock();
            _setret(ParserRet::SUCCESS);
            return ParserJsonObject(this->pj_center_, const_cast<rapidjson::Value*>(&(itr->value)));
        }
    } else {
        PARSER_ERROR("Not correct type");
        _setret(ParserRet::EMAHTYPE);
        this->pj_center_->UnLock();
        return ParserJsonObject();
    }
}

//ParserJson class
ParserJson::ParserJson()
{
    this->init_flag_ = false;
    this->thread_safe_flag_ = false;
}

ParserJson::~ParserJson()
{

}

ParserRet ParserJson::ParserJsonFile(const char* filename)
{
    if (access(filename, F_OK|R_OK)) {
        PARSER_ERROR("Bad json file name[%s]", strerror(errno));
        return ParserRet::EBADARGS;
    }

    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        PARSER_ERROR("Can not open file[%s] [%s]", filename, strerror(errno));
        return ParserRet::EBADARGS;
    }

    char jsoncache[MAXJSONFILESIZE];
    memset(jsoncache, 0x00, sizeof(jsoncache));
    rapidjson::FileReadStream frs(fp, jsoncache, MAXJSONFILESIZE);
    if (this->doc_.ParseStream(frs).HasParseError()) {
        fclose(fp);
        PARSER_ERROR("Parser json file[%s] error", filename);
        return ParserRet::ERROR;
    }

    fclose(fp);
    return ParserRet::SUCCESS;
}

ParserRet ParserJson::ParserJsonString(const char* jsonstring)
{
    if (this->doc_.Parse(jsonstring).HasParseError()) {
        return ParserRet::ERROR;
    }
    return ParserRet::SUCCESS;
}

ParserRet ParserJson::StorageJsonFile(const char* filename)
{
    unlink(filename);

    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        PARSER_ERROR("Can not open file[%s] [%s]", filename, strerror(errno));
        return ParserRet::EBADARGS;
    }

    char jsoncache[MAXJSONFILESIZE];
    memset(jsoncache, 0x00, sizeof(jsoncache));
    rapidjson::FileWriteStream fws(fp, jsoncache, sizeof(jsoncache));
    rapidjson::Writer<rapidjson::FileWriteStream> writer(fws);
    this->doc_.Accept(writer);
    fclose(fp);
    return ParserRet::SUCCESS;
}

void ParserJson::setThreadSafe()
{
    this->thread_safe_flag_ = true;
}

void ParserJson::UnsetThreadSafe()
{
    this->thread_safe_flag_ = false;
}

ParserRet ParserJson::RLock()
{
    if (!(this->thread_safe_flag_)) {
        return ParserRet::SUCCESS;
    }
    if (this->rwlock_.RLock() != thread::ThreadRet::SUCCESS) {
        return ParserRet::ELOCK;
    }
    return ParserRet::SUCCESS;
}

ParserRet ParserJson::RLock(struct timespec* overtime)
{
    if (!(this->thread_safe_flag_)) {
        return ParserRet::SUCCESS;
    }
    if (this->rwlock_.RLock(overtime) != thread::ThreadRet::SUCCESS) {
        return ParserRet::ELOCK;
    }
    return ParserRet::SUCCESS;
}

ParserRet ParserJson::WLock()
{
    if (!(this->thread_safe_flag_)) {
        return ParserRet::SUCCESS;
    }
    if (this->rwlock_.WLock() != thread::ThreadRet::SUCCESS) {
        return ParserRet::ELOCK;
    }
    return ParserRet::SUCCESS;
}

ParserRet ParserJson::WLock(struct timespec* overtime)
{
    if (!(this->thread_safe_flag_)) {
        return ParserRet::SUCCESS;
    }
    if (this->rwlock_.WLock(overtime) != thread::ThreadRet::SUCCESS) {
        return ParserRet::ELOCK;
    }
    return ParserRet::SUCCESS;
}

ParserRet ParserJson::UnLock()
{
    if (!(this->thread_safe_flag_)) {
        return ParserRet::SUCCESS;
    }
    if (this->rwlock_.UnLock() != thread::ThreadRet::SUCCESS) {
        return ParserRet::ELOCK;
    }
    return ParserRet::SUCCESS;
}

ParserJsonObject ParserJson::find(const char* path)
{
    if (rapidjson::Value* data = rapidjson::Pointer(path).Get(this->doc_)) {
        return ParserJsonObject(this, data);
    } else {
        return ParserJsonObject();
    }
}

} //namespace end
