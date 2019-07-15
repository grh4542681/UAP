#ifndef __IPV4_H__
#define __IPV4_H__

#include <string>

namespace util::ip {

class Ipv4 {
public:
    Ipv4();
    ~Ipv4();

    std::string GetString();
    int GetInt();

    static Ipv4 GetLocal();
    static Ipv4 GetLocal(std::string ifname);
private:
    std::string ifname_ = "";
    int ifip_ = 0;
};

}

#endif
