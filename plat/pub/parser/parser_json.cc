#include <unistd.h>

#include "parser_log.h"
#include "parser_return.h"
#include "parser_json.h"

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"

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

/**
* @brief isLong - Determine if the value of the current object is a long
*
* @returns  
*/
bool ParserJsonObject::isLong()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return false;
    }
    _setret(ParserRet::SUCCESS);
    return this->rpj_value_->IsInt64();
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

/**
* @brief getLong - If the current object is of type long, then get its value.
*
* @param [cache] - Cache address.
*
* @returns  ParserRet
*/
ParserRet ParserJsonObject::getLong(long* cache)
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
    if (this->rpj_value_->IsInt64()) {
        *cache = this->rpj_value_->GetInt64();
        this->pj_center_->UnLock();
        return ParserRet::SUCCESS;
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
}

/**
* @brief getLong - If the current object is of type long, then get its value.
*                  This function will block until other thread change this object done.
*
* @param [cache] - Cache address.
* @param [overtime] - Over time.
*
* @returns  ParserRet
*/
ParserRet ParserJsonObject::getLong(long* cache, struct timespec* overtime)
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
    if (this->rpj_value_->IsInt64()) {
        *cache = this->rpj_value_->GetInt64();
        this->pj_center_->UnLock();
        return ParserRet::SUCCESS;
    }
    this->pj_center_->UnLock();
    return ParserRet::ENOTFOUND;
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


/**
* @brief setString - Set this object as a string object.
*
* @param [cache] - Cache address.
* @param [cache_size] - Cache size.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setString(char* cache, unsigned int cache_size)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetString(cache, cache_size, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setString - Set this object as a string object.
*                    This function will block until other thread change this object done.
*
* @param [cache] - Cache address.
* @param [cache_size] - Cache size.
* @param [overtime] - Over time.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setString(char* cache, unsigned int cache_size, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetString(cache, cache_size, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setInt - Set this object as a int object.
*
* @param [cache] - Value.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setInt(int cache)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetInt(cache);
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setInt - Set this object as a int object.
*                 This function will block until other thread change this object done.
*
* @param [cache] - Value.
* @param [overtime] - Over time.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setInt(int cache, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetInt(cache);
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setLong - Set this object as a long object.
*
* @param [cache] - Value.
*
* @returns  Self reference
*/
ParserJsonObject& ParserJsonObject::setLong(long cache)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetInt64(cache);
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setLong - Set this object as a long object.
*                  This function will block until other thread change this object done.
*
* @param [cache] - Value.
* @param [overtime] - Over time.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setLong(long cache, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetInt64(cache);
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setDouble - Set this object as a double object.
*
* @param [cache] - Value.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setDouble(double cache)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetDouble(cache);
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setDouble - Set this object as a double object.
*                    This function will block until other thread change this object done.
*
* @param [cache] - Value.
* @param [overtime] - Overtime.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setDouble(double cache, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetDouble(cache);
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setNull - Set this object as a null object.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setNull()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetNull();
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setNull - Set this object as a null object.
*                  This function will block until other thread change this object done.
*
* @param [overtime] - Overtime.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setNull(struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetNull();
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setBool - Set this object as a bool object.
*
* @param [cache] - Value.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setBool(bool cache)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetBool(cache);
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setBool - Set this object as a bool object.
*                  This function will block until other thread change this object done.
*
* @param [cache] - Value.
* @param [overtime] - Overtime.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setBool(bool cache, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetBool(cache);
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setArray - Set this object as an empty array object.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setArray()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetArray();
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setArray - Set this object as an empty array object.
*                   This function will block until other thread change this object done.
*
* @param [overtime] - Over time.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setArray(struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetArray();
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setObject - Set this object as an empty object.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setObject()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetObject();
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

/**
* @brief setObject - Set this object as an empty object.
*                    This function will block until other thread change this object done.
*
* @param [overtime] - Over time.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::setObject(struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->SetObject();
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserRet ParserJsonObject::arraySize(unsigned int* size)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return (ParserRet::EINIT);
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        return (ParserRet::EMAHTYPE);
    }
    if ((this->pj_center_->RLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return (ParserRet::EGETRLOCK);
    }
    *size = this->rpj_value_->Size();
    this->pj_center_->UnLock();
    return (ParserRet::SUCCESS);
}

ParserJsonObject& ParserJsonObject::arrayPush(const char* value)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->PushBack(rapidjson::Value(value, this->pj_center_->doc_.GetAllocator()).Move(), this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}


ParserJsonObject& ParserJsonObject::arrayPush(const char* value, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->PushBack(rapidjson::Value(value, this->pj_center_->doc_.GetAllocator()).Move(), this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(const char* value, unsigned int len)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    rapidjson::Value rvalue(value, len, this->pj_center_->doc_.GetAllocator());
    this->rpj_value_->PushBack(rvalue, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(const char* value, unsigned int len, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    rapidjson::Value rvalue(value, len, this->pj_center_->doc_.GetAllocator());
    this->rpj_value_->PushBack(rvalue, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(int value)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->PushBack(value, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(int value, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->PushBack(value, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(long value)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->PushBack(value, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(long value, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->PushBack(value, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(double value)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->PushBack(value, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(double value, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->PushBack(value, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(bool value)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if ((this->pj_center_->WLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->PushBack(value, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(bool value, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if ((this->pj_center_->WLock(overtime)) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->PushBack(value, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(JsonType type, unsigned int size)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
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
    for (unsigned int loop =0; loop < size; loop++) {
        rapidjson::Value rvalue(value_type);
        this->rpj_value_->PushBack(rvalue, this->pj_center_->doc_.GetAllocator());
    }
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(JsonType type, unsigned int size, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
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
    for (unsigned int loop =0; loop < size; loop++) {
        rapidjson::Value rvalue(value_type);
        this->rpj_value_->PushBack(rvalue, this->pj_center_->doc_.GetAllocator());
    }
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(ParserJson& jsontree)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if (this->pj_center_->WLock() != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    rapidjson::Value rvalue;
    rvalue.CopyFrom(jsontree.doc_, this->pj_center_->doc_.GetAllocator());
    this->rpj_value_->PushBack(rvalue, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPush(ParserJson& jsontree, struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if (this->pj_center_->WLock(overtime) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    rapidjson::Value rvalue;
    rvalue.CopyFrom(jsontree.doc_, this->pj_center_->doc_.GetAllocator());
    this->rpj_value_->PushBack(rvalue, this->pj_center_->doc_.GetAllocator());
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPop()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if (this->pj_center_->WLock() != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->PopBack();
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayPop(struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if (this->pj_center_->WLock(overtime) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->PopBack();
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayClear()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if (this->pj_center_->WLock() != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->Clear();
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
}

ParserJsonObject& ParserJsonObject::arrayClear(struct timespec* overtime)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        _setret(ParserRet::EINIT);
        return *this;
    }
    if (!this->rpj_value_->IsArray()) {
        PARSER_ERROR("This object type is not Array");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
    if (this->pj_center_->WLock(overtime) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get write lock error!");
        _setret(ParserRet::EGETWLOCK);
        return *this;
    }
    this->rpj_value_->Clear();
    this->pj_center_->UnLock();
    _setret(ParserRet::SUCCESS);
    return *this;
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

ParserRet ParserJsonObject::objectSize(unsigned int* size)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return (ParserRet::EINIT);
    }
    if (this->rpj_value_->IsObject()) {
        ParserRet ret;
        if ((ret = this->pj_center_->RLock()) != ParserRet::SUCCESS) {
            PARSER_ERROR("Get read lock error!");
            return (ParserRet::EGETRLOCK);
        }
        *size = this->rpj_value_->MemberCount();
        this->pj_center_->UnLock();
        return (ParserRet::SUCCESS);
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        return (ParserRet::EMAHTYPE);
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

/**
* @brief objectAdd - If the current object is of type object, then add a child object.
*                    This function add a int object.
*
* @param [key] - Object name.
* @param [value] - Int address.
*
* @returns  Self reference.
*/
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

/**
* @brief objectAdd - If the current object is of type object, then add a child object.
*                    This function add a int object.
*                    This function will block until other thread change this object done.
*
* @param [key] - Object name.
* @param [value] - Int address.
* @param [overtime] - Over time.
*
* @returns  Self reference.
*/
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

/**
* @brief objectAdd - If the current object is of type object, then add a child object.
*                    This function add a long object.
*
* @param [key] - Object name.
* @param [value] - Long address.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::objectAdd(const char* key, long value)
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

/**
* @brief objectAdd - If the current object is of type object, then add a child object.
*                    This function add a long object.
*                    This function will block until other thread change this object done.
*
* @param [key] - Object name.
* @param [value] - Long address.
* @param [overtime] - Over time.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::objectAdd(const char* key, long value, struct timespec* overtime)
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

/**
* @brief objectAdd - If the current object is of type object, then add a child object.
*                    This function add a double object.
*
* @param [key] - Object name.
* @param [value] - Double address.
*
* @returns  Self reference.
*/
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

/**
* @brief objectAdd - If the current object is of type object, then add a child object.
*                    This function add a double object.
*                    This function will block until other thread change this object done.
*
* @param [key] - Object name.
* @param [value] - Double address.
* @param [overtime] - Over time.
*
* @returns  Self reference.
*/
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

/**
* @brief objectAdd - If the current object is of type object, then add a child object.
*                    This function add a bool object.
*
* @param [key] - Object name.
* @param [value] - Bool address.
*
* @returns  Self reference.
*/
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

/**
* @brief objectAdd - If the current object is of type object, then add a child object.
*                    This function add a bool object.
*                    This function will block until other thread change this object done.
*
* @param [key] - Object name.
* @param [value] - Bool address.
* @param [overtime] - Over time.
*
* @returns  Self refrence.
*/
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

/**
* @brief objectAdd - If the current object is of type object, then add a child object.
*                    This function add an empty object with specified type.
*
* @param [key] - Object name.
* @param [type] - Json type defined in header.
*
* @returns  Self reference.
*/
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

/**
* @brief objectAdd - If the current object is of type object, then add a child object.
*                    This function add an empty object with specified type.
*
* @param [key] - Object name.
* @param [type] - Json type
* @param [overtime] - Over time.
*
* @returns  Self reference.
*/
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

/**
* @brief objectAdd - If the current object is of type object, then add a child object.
*                    This function add a sub tree object.
*
* @param [key] - Object name.
* @param [jsontree] - Sub tree.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::objectAdd(const char* key, ParserJson& jsontree)
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
        rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
        rapidjson::Value rvalue;
        rvalue.CopyFrom(jsontree.doc_, this->pj_center_->doc_.GetAllocator());
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
*                    This function add a sub tree object.
*                    This function will block until other thread change this object done.
*
* @param [key] - Object name.
* @param [jsontree] - Sub tree.
* @param [overtime] - Over time.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::objectAdd(const char* key, ParserJson& jsontree, struct timespec* overtime)
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
        rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
        rapidjson::Value rvalue;
        rvalue.CopyFrom(jsontree.doc_, this->pj_center_->doc_.GetAllocator());
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
* @brief objectDel - If the current object is of type object, then delete specified key object.
*
* @param [key] - Object name.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::objectDel(const char* key)
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
        if (this->rpj_value_->EraseMember(key)) {
            this->pj_center_->UnLock();
            _setret(ParserRet::SUCCESS);
            return *this;
        } else {
            this->pj_center_->UnLock();
            PARSER_ERROR("Not found child object [%s]", key);
            _setret(ParserRet::ENOTFOUND);
            return *this;
        }
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }

}

/**
* @brief objectDel - If the current object is of type object, then delete specified key object.
*                    This function will block until other thread change this object done.
*
* @param [key] - Object name.
* @param [overtime] - Over time.
*
* @returns  Self reference.
*/
ParserJsonObject& ParserJsonObject::objectDel(const char* key, struct timespec* overtime)
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
        if (this->rpj_value_->EraseMember(key)) {
            this->pj_center_->UnLock();
            _setret(ParserRet::SUCCESS);
            return *this;
        } else {
            this->pj_center_->UnLock();
            PARSER_ERROR("Not found child object [%s]", key);
            _setret(ParserRet::ENOTFOUND);
            return *this;
        }
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
}

ParserJsonObject& ParserJsonObject::objectClear()
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
        this->rpj_value_->RemoveAllMembers();
        this->pj_center_->UnLock();
        _setret(ParserRet::SUCCESS);
        return *this;
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        _setret(ParserRet::EMAHTYPE);
        return *this;
    }
}

ParserJsonObject& ParserJsonObject::objectClear(struct timespec* overtime)
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
        this->rpj_value_->RemoveAllMembers();
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
* @brief Vfind - Longitudinally find the node of the specified path.
*                If find new node, it will change self point to new node.
*
* @param [path] - Like xpath "/a/b/c/d".
*
* @returns  Self reference.
*/
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

/**
* @brief Hfind - Horizontally looking up the node of the specified path
*                Not support now.
*
* @param [name] - 
*
* @returns  
*/
ParserJsonObject& ParserJsonObject::Hfind(const char* name)
{
    PARSER_ERROR("Not support");
    return *this;
}

/**
* @brief operator[] - If the current object is of type array.
*                     Then you can manipulate the current object as you would an array.
*                     If find new node, it will change self point to new node.
*
* @param [index] - index.
*
* @returns  Self reference.
*/
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

/**
* @brief operator[] - If the current object is of type object.
*                     Then you can manipulate the current object as you would an map.
*                     If find new node, it will change self point to new node.
*
* @param [name] - object name.
*
* @returns  Self reference.
*/
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
    rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(fws);
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
    if (!strcmp(path, "/")) {
        return ParserJsonObject(this, &(this->doc_));
    } else {
        if (rapidjson::Value* data = rapidjson::Pointer(path).Get(this->doc_)) {
            return ParserJsonObject(this, data);
        } else {
            return ParserJsonObject();
        }
    }
}

} //namespace end
