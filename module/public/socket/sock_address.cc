#include "sock_address.h"

namespace sock {

SockAddress::SockAddress()
{
    this->init_flag_ = false;
}
SockAddress(SockFamily family, unsigned short int port)
{
    _init(family, port);
}
SockAddress(SockFamily family, char* address, unsigned short int port)
{
    _init(family, address, port);
}
SockAddress(SockFamily family, char* address)
{
    _init(family, address);
}

SockRet SockAddress::_init(SockFamily family, unsigned short int port)
{
    switch(family_){
        case SockFamily::TCP_INET4:
            this->domain_ = AF_INET;
            this->type_ = SOCK_STREAM;
            break;
        case SockFamily::TCP_INET6:
            this->domain_ = AF_INET6;
            this->type_ = SOCK_STREAM;
            break;
        case SockFamily::UDP_INET4:
            this->domain_ = AF_INET;
            this->type_ = SOCK_DGRAM;
            break;
        case SockFamily::UDP_INET6:
            this->domain_ = AF_INET6;
            this->type_ = SOCK_DGRAM;
            break;
        case SockFamily::TCP_LOCAL:
        case SockFamily::UDP_LOCAL:
            SOCK_ERROR("%s", "Local socket need unixfile not port!");
            this->init_flag_ = false;
            return;
        default:
            SOCK_ERROR("%s", "Unknow socket family!");
            this->init_flag_ = false;
            return;
    }
    this->family_ = family;
    this->port = port;
    this->address_.clear();
    this->init_flag_ = true;
}

SockRet SockAddress::_init(SockFamily family, char* address, unsigned short int port)
{
    switch(this->family_){
        case SockFamily::TCP_INET4:
            this->domain_ = AF_INET;
            this->type_ = SOCK_STREAM;
            break;
        case SockFamily::TCP_INET6:
            this->domain_ = AF_INET6;
            this->type_ = SOCK_STREAM;
            break;
        case SockFamily::UDP_INET4:
            this->domain_ = AF_INET;
            this->type_ = SOCK_DGRAM;
            break;
        case SockFamily::UDP_INET6:
            this->domain_ = AF_INET6;
            this->type_ = SOCK_DGRAM;
            break;
        case SockFamily::TCP_LOCAL:
        case SockFamily::UDP_LOCAL:
            SOCK_ERROR("%s", "Local socket need unixfile not port!");
            this->init_flag_ = false;
            return;
        default:
            SOCK_ERROR("%s", "Unknow socket family!");
            this->init_flag_ = false;
            return;
    }
    this->family_ = family;
    this->port = port;    
    this->address_ = address;
    this->init_flag_ = true;
}

 SockRet SockAddress::_init(SockFamily family, char* address)
{
    switch(this->family_){
        case SockFamily::TCP_LOCAL:
            this->domain_ = AF_LOCAL;
            this->type_ = SOCK_STREAM;
            break;
        case SockFamily::UDP_LOCAL:
            this->domain_ = AF_LOCAL;
            this->type_ = SOCK_DGRAM;
            break;
        case SockFamily::TCP_INET4:
        case SockFamily::TCP_INET6:
        case SockFamily::UDP_INET4:
        case SockFamily::UDP_INET6:
            SOCK_ERROR("%s", "Inet socket need port!");
            this->init_flag_ = false;
            return;
        default:
            SOCK_ERROR("%s", "Unknow socket family!");
            this->init_flag_ = false;
            return;
    }
    this->family_ = family;
    this->address_ = address;
    this->init_flag_ = true;
}

bool SockAddress::AddrChecek()
{
    return this->init_flag_;
}

}//namespace sock end
