#ifndef __RETURN_H__
#define __RETURN_H__

#include <string>
#include <map>
#include <vector>

#include <errno.h>
#include <string.h>

#include "error_code_space_define.h"

namespace ret {

class Return {
public:
    typedef std::map<const int, const std::string> ECodeMapType;
    enum ECode{
        UNKNOW = -2,
        ERROR = -1,

        EBADARGS   = PUBLIC_ERROR_CODE_BASE,
        EMAP,
        ELIST,
        EVECTOR,
        EMALLOC,
        EINIT,
        ETIMEOUT,
        ESUBCLASS,
        ECONSTRUCT,
        ENONSUPPORT,

        ETHREAD,
        EPROCESS,
    };
public:
    const static int SUCCESS = 0;
    static ECodeMapType ECodeMap;
public:
    Return(int err_code) : err_code_(err_code) {
        err_code_vec_.push_back(&Return::ECodeMap);
    }
    Return(Return& other) {
        err_code_ = other.err_code_;
    }
    virtual ~Return() { }

    virtual int Code() const {
        return err_code_;
    }

    virtual const std::string Message() {
        std::string emgs = "";
        if (err_code_ >= 0 && err_code_ < ERROR_CODE_BASE) {
            emgs.assign(strerror(err_code_));
        } else {
            for (auto vit : err_code_vec_ ) {
                auto it = vit->find(err_code_);
                if (it != vit->end()) {
                    emgs = it->second;
                }
            }
        }
        return emgs;
    }

public:
    Return& operator=(const int err_code) {
        err_code_ = err_code;
        return *this;
    }
    Return& operator=(const Return& ret) {
        err_code_ = ret.Code();
        return *this;
    }
    Return& operator=(const Return&& ret) {
        err_code_ = ret.Code();
        return *this;
    }
    
    bool operator==(int err_code) {
        return (err_code_ == err_code);
    }
    bool operator==(Return& ret) {
        return (err_code_ == ret.Code());
    }
    bool operator==(Return&& ret) {
        return (err_code_ == ret.Code());
    }

    bool operator!=(int err_code) {
        return (err_code_ != err_code);
    }
    bool operator!=(Return& ret) {
        return (err_code_ != ret.Code());
    }
    bool operator!=(Return&& ret) {
        return (err_code_ != ret.Code());
    }

protected:
    int err_code_;
    std::vector<ECodeMapType*> err_code_vec_;
};

}

#endif
