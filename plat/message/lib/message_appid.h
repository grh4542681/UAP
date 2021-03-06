#ifndef __MESSAGE_APPID_H__
#define __MESSAGE_APPID_H__

#include <string>
#include <map>
#include <vector>

#include <errno.h>
#include <string.h>

#include "message_return.h"
#include "message_comid_define.h"

namespace message {

class MessageAppid {
public:
    typedef std::map<const int, const std::string> AppidMapType;
    enum Appid{
        Unknow = 0,

        MessageInternal = MESSAGE_INTERNAL_COMID,
        MessageReqHeartbeat,
        MessageRepHeartbeat,
        MessageReqConnect,
        MessageRepConnect,
        MessageAgentRegister,
        MessageAgentUnregister,
    };
public:
    static AppidMapType AppidMap;
public:
    MessageAppid(int appid = Appid::Unknow) : appid_(appid) {
        appid_map_vec_.push_back(&MessageAppid::AppidMap);
    }
    MessageAppid(const MessageAppid& other) {
        appid_ = other.appid_;
    }
    virtual ~MessageAppid() { }

    virtual int Code() const {
        return appid_;
    }

    virtual const std::string GetDescribe() {
        std::string emgs = "";
        for (auto vit : appid_map_vec_ ) {
            auto it = vit->find(appid_);
            if (it != vit->end()) {
                emgs = it->second;
                break;
            }
        }
        return emgs;
    }

public:
    MessageAppid& operator=(const int appid) {
        appid_ = appid;
        return *this;
    }
    MessageAppid& operator=(const MessageAppid& appid) {
        appid_ = appid.GetId();
        return *this;
    }
    MessageAppid& operator=(const MessageAppid&& appid) {
        appid_ = appid.GetId();
        return *this;
    }
    
    bool operator==(int appid) {
        return (appid_ == appid);
    }
    bool operator==(MessageAppid& appid) {
        return (appid_ == appid.GetId());
    }
    bool operator==(MessageAppid&& appid) {
        return (appid_ == appid.GetId());
    }

    bool operator!=(int appid) {
        return (appid_ != appid);
    }
    bool operator!=(MessageAppid& appid) {
        return (appid_ != appid.GetId());
    }
    bool operator!=(MessageAppid&& appid) {
        return (appid_ != appid.GetId());
    }

    int GetId() const {
        return appid_;
    }

protected:
    int appid_;
    std::vector<AppidMapType*> appid_map_vec_;
};

}

#endif
