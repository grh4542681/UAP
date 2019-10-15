#ifndef __CONFIG_RETURN_H__
#define __CONFIG_RETURN_H__

#include "return.h"

namespace config {

class ConfigRet : public ret::Return {
public:
    enum ECode{
        CONFIG_EBASE = CONFIG_ERROR_CODE_BASE,
        CONFIG_EPARSER,
        CONFIG_EGET,
    };
public:
    static ECodeMapType ECodeMap;
public:
    ConfigRet(int err_code = 0) : ret::Return(err_code) {
        err_code_vec_.push_back(&ConfigRet::ECodeMap);
    }
    ConfigRet(ConfigRet& other) : ret::Return(other) { }
    ~ConfigRet() { };
public:
    ConfigRet& operator=(const int err_code) {
        Return::operator=(err_code);
        return *this;
    }   
    ConfigRet& operator=(const ConfigRet& ret) {
        Return::operator=(ret);
        return *this;
    }   
    ConfigRet& operator=(const ConfigRet&& ret) {
        Return::operator=(ret);
        return *this;
    }
};
} // namespace cm

#endif
