#ifndef __NS_ENDPOINT_H__
#define __NS_ENDPOINT_H__

#include <string>

namespace ns{

class NsEndpoint {
public:
    NsEndpoint(std::string epname);
    NsEndpoint(const NsEndpoint&);
private:
};

}// namesapce ns end

#endif
