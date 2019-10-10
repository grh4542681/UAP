#ifndef __CONFIG_STATIC_H__
#define __CONFIG_STATIC_H__

#include "parser_josn.h""

namespace config {

template < typename P >
class ConfigStatic {
public:
    ConfigStatic();
    ~ConfigStatic() { }

    ConfigRet Load(std::string str) {

    }
    ConfigRet Load(file::File& file) {

    }

    template < typename T > ConfigRet Get(std::string path, T* data) {
        
    }
    template < typename T > ConfigRet Get(std::string path, std::vector<T>& vec) {

    }

private:
    parser::ParserJson parser_;
    
};

}

#endif
