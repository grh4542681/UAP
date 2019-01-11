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

ParserJsonObject::ParserJsonObject(const parser::ParserJsonObject& old)
{
    this->rpj_value_ = old.rpj_value_;
    this->pj_center_ = old.pj_center_;
    this->init_flag_ = old.init_flag_;
}

ParserJsonObject::~ParserJsonObject()
{

}

bool ParserJsonObject::isEmpty()
{
    return this->init_flag_;
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

bool ParserJsonObject::isArray()
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

ParserJsonObject& ParserJsonObject::objectAdd(const char* key, const char* value, unsigned int len)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return *this;
    }
    if (this->rpj_value_->IsObject()) {
        if (this->pj_center_->WLock() != ParserRet::SUCCESS) {
            PARSER_ERROR("Get write lock error!");
            return *this;
        }
        rapidjson::Value rvalue(value, len, this->pj_center_->doc_.GetAllocator());
        rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
        this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
        this->pj_center_->UnLock();
        return *this;
    } else {
        PARSER_ERROR("This object type is not OBJECT");
        return *this;
    }
}

ParserJsonObject& ParserJsonObject::objectAdd(const char* key, int value)
{
    rapidjson::Value rvalue(value);
    rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
    this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
    return *this;
}

ParserJsonObject& ParserJsonObject::objectAdd(const char* key, double value)
{
    rapidjson::Value rvalue(value);
    rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
    this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
    return *this;
}

ParserJsonObject& ParserJsonObject::objectAdd(const char* key, bool value)
{
    rapidjson::Value rvalue(value);
    rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
    this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
    return *this;
}

ParserJsonObject& ParserJsonObject::objectAdd(const char* key, JsonType type)
{
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
            return *this;
    }
    rapidjson::Value rvalue(value_type);
    rapidjson::Value rkey(key, this->pj_center_->doc_.GetAllocator());
    this->rpj_value_->AddMember(rkey, rvalue, this->pj_center_->doc_.GetAllocator());
    return *this;
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
    PARSER_ERROR("Not support");
    return *this;
}

ParserJsonObject ParserJsonObject::operator[](int index)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserJsonObject();
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ParserJsonObject();
    }
    if (this->rpj_value_->IsArray()) {
        if (index < 0 || static_cast<unsigned int>(index) > this->rpj_value_->Size()) {
            this->pj_center_->UnLock();
            return ParserJsonObject();
        } else {
            this->pj_center_->UnLock();
            return ParserJsonObject(this->pj_center_, &((*(this->rpj_value_))[index]));
        }
    }
    this->pj_center_->UnLock();
    return ParserJsonObject();
}

ParserJsonObject ParserJsonObject::operator[](const char* name)
{
    if (!this->init_flag_) {
        PARSER_ERROR("This object has not init");
        return ParserJsonObject();
    }
    ParserRet ret;
    if ((ret = this->pj_center_->RLock()) != ParserRet::SUCCESS) {
        PARSER_ERROR("Get read lock error!");
        return ParserJsonObject();
    }
    if (this->rpj_value_->IsObject()) {
        rapidjson::Value::ConstMemberIterator itr = this->rpj_value_->FindMember(name);
        if (itr == this->rpj_value_->MemberEnd()) {
            this->pj_center_->UnLock();
            return ParserJsonObject();
        } else {
            this->pj_center_->UnLock();
            return ParserJsonObject(this->pj_center_, const_cast<rapidjson::Value*>(&(itr->value)));
        }
    } else {
        PARSER_ERROR("Not correct type");
        this->pj_center_->UnLock();
        return ParserJsonObject();
    }
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
