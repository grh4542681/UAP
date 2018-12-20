#ifndef __NS_ENDPOINT_H__
#define __NS_ENDPOINT_H__

#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>

#include "ns_monitor.h"

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

typedef struct _NsEndPointInfo {
    std::string ep_name_;
    DevInfo dev_info_;
    ThreadInfo thread_info_;
    NsMonitorInfo monitor_info_;
}NsEndPointInfo;

class NsEndPoint {
public:
    static NsEndPoint* getInstance();
    static NsEndPoint* getInstance(std::string ep_name);

    NsRet Register();
    NsRet Update();
    NsRet Unregister();

    NsRet Send(std::string dest_ep_name);
private:
    NsEndPoint(std::string epname);
    NsEndPoint(const NsEndPoint&);
    ~NsEndPoint();

    bool init_flag_;
    NsEndPointInfo ep_info_;
    thread_local static NsEndPoint* pInstance;

    bool _init();
    bool IsSameProc(NsEndPoint&);
    bool IsSameDev(NsEndPoint&);
};

}// namesapce ns end

#endif
