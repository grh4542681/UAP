#include <unistd.h>

#include "parser_log.h"
#include "parser_return.h"
#include "parser_json.h"

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

namespace parser {

//ParserJsonObject class
ParserJsonObject::ParserJsonObject(ParserJson* pj_center, rapidjson::Value* rpj_value)
{
    this->rpj_value_ = rpj_value;
    this->pj_center_ = pj_center;
    this->free_flag_ = false;
}

ParserJsonObject::~ParserJsonObject()
{

}

void ParserJsonObject::Free()
{
    this->free_flag_ = true;
}

bool ParserJsonObject::isString()
{

}

bool ParserJsonObject::isInt()
{

}

bool ParserJsonObject::isDouble()
{

}

bool ParserJsonObject::isVector()
{

}

bool ParserJsonObject::isStruct()
{

}
    
ParserRet ParserJsonObject::getString(char* cache, unsigned int cache_size)
{
    if (this->free_flag_) {
        PARSER_ERROR("This object has already been free");
        return ParserRet::EINIT;
    }
    if (this->rpj_value_->IsString()) {
        if (cache_size > this->rpj_value_->GetStringLength()) {
            memcpy(cache, this->rpj_value_->GetString(), this->rpj_value_->GetStringLength());
            return ParserRet::SUCCESS;
        } else {
            PARSER_ERROR("Cache size is not enough, need at least [%d]",this->rpj_value_->GetStringLength());
            return ParserRet::EBADARGS;
        }
    }
    return ParserRet::ENOTFOUND;
}
    
ParserRet ParserJsonObject::getInt(int* cache)
{

}
    
ParserRet ParserJsonObject::getDouble(double* cache)
{

}
    
ParserRet ParserJsonObject::getVector(std::vector<ParserJsonObject*>* cache)
{

}
    
ParserRet ParserJsonObject::getStruct()
{

}

ParserJsonObject* ParserJsonObject::find(const char* path)
{
    if (this->free_flag_) {
        PARSER_ERROR("This object has already been free");
        return NULL;
    }
    if (rapidjson::Value* data = rapidjson::Pointer(path).Get(*(this->rpj_value_))) {
        this->rpj_value_ = data;
        return this;
    } else {
        PARSER_ERROR("Can not find path[%s]", path);
        return NULL;
    }
}

//ParserJson class
ParserJson::ParserJson()
{
    this->init_flag_ = false;
}

ParserJson::~ParserJson()
{
    for (auto it : this->object_list_) {
        this->mempool_->Free<ParserJsonObject>(it);
        printf("--------\n");
    }
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

ParserJsonObject* ParserJson::find(const char* path)
{
    if (rapidjson::Value* data = rapidjson::Pointer(path).Get(this->doc_)) {
        ParserJsonObject* pobject = NULL;
        for (auto it : this->object_list_) {
            if (it->free_flag_) {
                pobject = it;
                it->free_flag_ = false;
                it->rpj_value_ = data;
            }
        }
        if (!pobject) {
            pobject = this->mempool_->Malloc<ParserJsonObject>(this, data);
            this->object_list_.push_back(pobject);
        }
        return pobject;
    } else {
        PARSER_ERROR("Can not find path[%s]", path);
        return NULL;
    }
}

ParserRet ParserJson::getString(const char* path, char* cache, unsigned int cache_size)
{
    if (rapidjson::Value* data = rapidjson::Pointer(path).Get(this->doc_)) {
        if (data->IsString()) {
            if (cache_size > data->GetStringLength()) {
                memcpy(cache, data->GetString(), data->GetStringLength());
                return ParserRet::SUCCESS;
            }
        }
    }
    return ParserRet::ERROR;
}

} //namespace end
