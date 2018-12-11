#ifndef __SOCK_ADDRESS_H__
#define __SOCK_ADDRESS_H__

#include <string>

#include <sys/socket.h>
#include "sock_common.h"
#include "sock_return.h"

namespace sock{

class SockAddress {
public:
    friend class SockFD;
    friend class SockServer;
    friend class SockClient;
    SockAddress();
    SockAddress(SockFamily family, unsigned short int port):family_(family){
        this->_init(family, port);
    }
    SockAddress(SockFamily family, const char* address, unsigned short int port):family_(family){
        this->_init(family, address, port);
    }
    SockAddress(SockFamily family, const char* address):family_(family){
        this->_init(family, address);
    }

    sockaddr* getSockaddr();
    unsigned short int getPort();
    bool isLocal();
    bool AddrCheck();
private:
    bool init_flag_;

    SockFamily family_;
    std::string address_;
    unsigned short int port_;
    int domain_;
    int type_;

    SockRet _init(SockFamily family, unsigned short int port);
    SockRet _init(SockFamily family, const char* address, unsigned short int port);
    SockRet _init(SockFamily family, const char* address);
};

}

#endif
