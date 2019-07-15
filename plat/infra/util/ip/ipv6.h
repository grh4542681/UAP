#ifndef __IPV6_H__
#define __IPV6_H__

#include <string>

namespace util::ip {

class Ipv6 {
public:
    Ipv6();
    ~Ipv6();

    std::string GetString();
    int GetInt();

    static Ipv6 GetLocal();
    static Ipv6 GetLocal(std::string ifname);
private:
    std::string ifname_ = "";
    int ifip_ = 0;
};

}

#endif
