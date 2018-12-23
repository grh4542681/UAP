#ifndef __NS_DAEMON_H__
#define __NS_DAEMON_H__

#include <list>
#include <map>
#include "ns_endpoint.h"

namespace ns{

class NsDaemon{
public:
    NsDaemon();
    ~NsDaemon();
private:
    std::map<std::string,std::list<NsEndPointInfo*>> ep_table_;
};

}

#endif
