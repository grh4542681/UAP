#ifndef __SOCK_ADDRESS_H__
#define __SOCK_ADDRESS_H__

#include <string>

#include <sys/socket.h>
#include "sock_common.h"

namespace sock{

class SockAddress {
public:
    friend class SockServer;
    SockAddress(SockFamily family, unsigned short int port);
    SockAddress(SockFamily family, char* address, unsigned short int port);
    SockAddress(SockFamily family, char* address);

    sockaddr* getSockaddr();
    unsigned short int getPort();
    bool isLocal();
    bool AddrChecek();
private:
    bool init_flag_;

    SockFamily family_;
    std::string address_;
    unsigned short int port_;
    int domain_;
    int type_;

};

}

#endif
