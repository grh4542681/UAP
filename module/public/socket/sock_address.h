#ifndef __SOCK_ADDRESS_H__
#define __SOCK_ADDRESS_H__

#include <sys/socket.h>

namespace sock{

class SockAddress {
public:

    SockAddress(unsigned short int port);
    SockAddress(char* address, unsigned short int port);
    SockAddress(char* unixfile);

    sockaddr* getSockaddr();
    unsigned short int getPort();
    bool isLocal();
private:
    sockaddr address_;
    unsigned short int port_;

};

}

#endif
