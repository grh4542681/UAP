#ifndef __NS_ENDPOINT_H__
#define __NS_ENDPOINT_H__

#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>

namespace ns{

typedef struct _DevInfo {
    struct in_addr sin_addr;
    struct in6_addr sin6_addr;
    unsigned char mac[6];
}DevInfo;

typedef struct _ThreadInfo {
    pid_t pid;
    pthread_t tid;
}ThreadInfo;

typedef struct _EpState {
    int state;
}EpState;

class NsEndPointInfo {
public:
    friend class NsEndPoint;
    NsEndPointInfo();
    NsEndPointInfo(NsEndPointInfo&);
    ~NsEndPointInfo();

    bool IsSameEp(NsEndPointInfo&);
    bool IsSameProc(NsEndPointInfo&);
    bool IsSameDev(NsEndPointInfo&);
private:
    std::string ep_name_;
    DevInfo dev_info_;
    ThreadInfo thread_info_;
    EpState state_info_;
};

class NsEndPoint {
public:
    NsEndPoint(std::string epname);
    NsEndPoint(const NsEndPoint&);

    NsRet Register();
    NsRet Update();
    NsRet Unregister();

    NsRet Send();
    NsRet Recv();

    static NsRet Lookup(NsEndPoint*, std::string ep_name);
private:
    ~NsEndPoint();

    bool init_flag_;
    NsEndPointInfo ep_info_;
    thread_local static NsEndPoint* pInstance;

    bool _init();
};

}// namesapce ns end

#endif
