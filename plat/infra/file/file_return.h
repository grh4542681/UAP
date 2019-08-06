#ifndef __FILE_RETURN_H__
#define __FILE_RETURN_H__

#include "return.h"

namespace file {

class FileRet : public ret::Return {
public:
    enum ECode{
        FILE_EBASE = FILE_ERROR_CODE_BASE,
        FILE_ESTATE,
        FILE_EACCES,
        FILE_EFAULT,
        FILE_EINVAL,
        FILE_EIO,
        FILE_ELOOP,
        FILE_ENAMETOOLONG,
        FILE_ENOENT,
        FILE_ENOMEM,
        FILE_ENOTDIR,
        FILE_EMODE,
    };
public:
    static ECodeMapType ECodeMap;
public:
    FileRet(int err_code = 0) : ret::Return(err_code) {
        err_code_vec_.push_back(&FileRet::ECodeMap);
    }
    FileRet(FileRet& other) : ret::Return(other) { }
    ~FileRet() { };
public:
    FileRet& operator=(int err_code) {
        Return::operator=(err_code);
        return *this;
    }   
    FileRet& operator=(FileRet& ret) {
        Return::operator=(ret);
        return *this;
    }   
    FileRet& operator=(FileRet&& ret) {
        Return::operator=(ret);
        return *this;
    }
};

}

#endif
