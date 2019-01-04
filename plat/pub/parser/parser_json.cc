#include <unistd.h>

#include "parser_log.h"
#include "parser_return.h"
#include "parser_json.h"

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

namespace parser {

//ParserJsonObject class
ParserJsonObject::ParserJsonObject(rapidjson::Value* rpjValue)
{
    this->rpjValue_ = rpjValue;
}

ParserJsonObject::~ParserJsonObject()
{

}

bool ParserJsonObject::isString(){

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

//ParserJson class
ParserJson::ParserJson()
{
    this->init_flag_ = false;
}

ParserJson::~ParserJson()
{
    for (auto it : this->object_map_) {
        this->mempool_->Free(it.second);
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

ParserJsonObject* ParserJson::get(const char* path)
{
    std::map<std::string, ParserJsonObject*>::iterator it;
    it = this->object_map_.find(path);
    if (it != this->object_map_.end()) {
        return it->second;
    }

    if (rapidjson::Value* data = rapidjson::Pointer(path).Get(this->doc_)) {
        ParserJsonObject* pobject = this->mempool_->Malloc<ParserJsonObject>(data);
        this->object_map_.insert(std::pair<std::string, ParserJsonObject*>(path, pobject));
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
