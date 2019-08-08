#ifndef __MESSAGE_RETURN_H__
#define __MESSAGE_RETURN_H__

#include "return.h"

namespace message {

class MessageRet : public ret::Return {
public:
    enum ECode{
        MESSAGE_EBASE = PARSER_ERROR_CODE_BASE,
        MESSAGE_EMSNOSPACE,
        MESSAGE_EMSNOMESSG,
        MESSAGE_EMSMODE,
    };
public:
    static ECodeMapType ECodeMap;
public:
    MessageRet(int err_code = 0) : ret::Return(err_code) {
        err_code_vec_.push_back(&MessageRet::ECodeMap);
    }
    MessageRet(MessageRet& other) : ret::Return(other) { }
    ~MessageRet() { };
public:
    MessageRet& operator=(const int err_code) {
        Return::operator=(err_code);
        return *this;
    }   
    MessageRet& operator=(const MessageRet& ret) {
        Return::operator=(ret);
        return *this;
    }   
    MessageRet& operator=(const MessageRet&& ret) {
        Return::operator=(ret);
        return *this;
    }
};

}

#endif
