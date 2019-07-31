#ifndef __RETURN_H__
#define __RETURN_H__

#include <string>
#include <map>
#include <vector>

#include "error_code_space_define.h"

namespace ret {

class Return {
public:
    enum ECode{
        UNKNOW = -2,
        ERROR = -1,
        SUCCESS = 0,

        EBADARGS = PUBLIC_ERROR_CODE_BASE,
    };
public:
    static std::map<const int, const std::string> ECodeMap;
public:
    Return(int err_code) : err_code_(err_code) {
        err_code_vec_.push_back(&Return::ECodeMap);
    }
    virtual ~Return() { }

    virtual int Code() {
        return err_code_;
    }

    virtual const std::string Message() {
        for (auto vit : err_code_vec_ ) {
            auto it = vit->find(err_code_);
            if (it != vit->end()) {
                return it->second;
            }
        }
        return std::string("");
    }

protected:
    int err_code_;
    std::vector<std::map<const int, const std::string>* > err_code_vec_;
};

}

#endif
