#include <unistd.h>

#include "parser_log.h"
#include "parser_return.h"
#include "parser_json.h"

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

namespace parser {

//ParserJsonObject class
ParserJsonObject::ParserJsonObject()
{
    this->rpj_value_ = NULL;
    this->pj_center_ = NULL;
    this->init_flag_ = true;
}

ParserJsonObject::ParserJsonObject(ParserJson* pj_center, rapidjson::Value* rpj_value)
{
    this->rpj_value_ = rpj_value;
    this->pj_center_ = pj_center;
    if (!rpj_value || !pj_center) {
        this->init_flag_ = false;
    } else {
        this->init_flag_ = true;
    }
}

ParserJsonObject::~ParserJsonObject()
{

}

bool ParserJsonObject::isString()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return false;
    }
    return this->rpj_value_->IsString();
}

bool ParserJsonObject::isInt()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return false;
    }
    return this->rpj_value_->IsInt();
}

bool ParserJsonObject::isDouble()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return false;
    }
    return this->rpj_value_->IsDouble();
}

bool ParserJsonObject::isNull()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return false;
    }
    return this->rpj_value_->IsNull();
}

bool ParserJsonObject::isBool()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return false;
    }
    return this->rpj_value_->IsBool();
}

bool ParserJsonObject::isVector()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return false;
    }
    return this->rpj_value_->IsArray();
}

bool ParserJsonObject::isStruct()
{

}
    
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
    
ParserRet ParserJsonObject::getVector(std::vector<ParserJsonObject>* cache)
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
        return ParserRet::SUCCESS;
    }
    return ParserRet::ENOTFOUND;
}

ParserRet ParserJsonObject::getVector(std::vector<ParserJsonObject>* cache, struct timespec* overtime)
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
        return ParserRet::SUCCESS;
    }
    return ParserRet::ENOTFOUND;
}
    
ParserRet ParserJsonObject::getStruct()
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserRet::EINIT;
    }

}

ParserJsonObject& ParserJsonObject::Vfind(const char* path)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return *this;
    }
    if (rapidjson::Value* data = rapidjson::Pointer(path).Get(*(this->rpj_value_))) {
        this->rpj_value_ = data;
        return *this;
    } else {
        PARSER_ERROR("Can not find path[%s]", path);
        return *this;
    }
}

ParserJsonObject& ParserJsonObject::Hfind(const char* name)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return *this;
    }
    for (rapidjson::Value::ConstMemberIterator itr = this->rpj_value->MemberBegin();itr != this->rpj_value->MemberEnd(); ++itr) {
        if (!strcmp(itr->name.GetString(), name)) {
            this->rpj_value_ = it;
            return *this;
        }
    }
    PARSER_ERROR("Can not find path[%s]", name);
    return *this;
}

//ParserJson class
ParserJson::ParserJson()
{
    this->init_flag_ = false;
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

ParserRet ParserJson::RLock()
{
    if (this->rwlock_.RLock() != thread::ThreadRet::SUCCESS) {
        return ParserRet::ELOCK;
    }
    return ParserRet::SUCCESS;
}

ParserRet ParserJson::RLock(struct timespec* overtime)
{
    if (this->rwlock_.RLock(overtime) != thread::ThreadRet::SUCCESS) {
        return ParserRet::ELOCK;
    }
    return ParserRet::SUCCESS;
}

ParserRet ParserJson::WLock()
{
    if (this->rwlock_.WLock() != thread::ThreadRet::SUCCESS) {
        return ParserRet::ELOCK;
    }
    return ParserRet::SUCCESS;
}

ParserRet ParserJson::WLock(struct timespec* overtime)
{
    if (this->rwlock_.WLock(overtime) != thread::ThreadRet::SUCCESS) {
        return ParserRet::ELOCK;
    }
    return ParserRet::SUCCESS;
}

ParserRet ParserJson::UnLock()
{
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
