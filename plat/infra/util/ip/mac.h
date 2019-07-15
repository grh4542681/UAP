#ifndef __MAC_H__
#define __MAC_H__

#include <string>

namespace util::ip {

class Mac {
public:
    Mac();
    ~Mac();

    static Mac GetLocal();
    static Mac GetLocal(std::string ifname);

private:
    std::string ifname_;
    std::string ifmac_;
};

}

#endif
