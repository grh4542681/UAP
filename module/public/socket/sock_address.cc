#include "sock_address.h"
#include "sock_log.h"

namespace sock {

SockAddress::SockAddress()
{
    this->init_flag_ = false;
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
            return SockRet::EINIT;
        default:
            SOCK_ERROR("%s", "Unknow socket family!");
            this->init_flag_ = false;
            return SockRet::EINIT;
    }
    this->family_ = family;
    this->port_ = port;
    this->address_.clear();
    this->init_flag_ = true;
    return SockRet::SUCCESS;
}

SockRet SockAddress::_init(SockFamily family, const char* address, unsigned short int port)
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
            return SockRet::EINIT;
        default:
            SOCK_ERROR("%s", "Unknow socket family!");
            this->init_flag_ = false;
            return SockRet::EINIT;
    }
    this->family_ = family;
    this->port_ = port;    
    this->address_ = address;
    this->init_flag_ = true;
    return SockRet::SUCCESS;
}

SockRet SockAddress::_init(SockFamily family, const char* address)
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
            return SockRet::EINIT;
        default:
            SOCK_ERROR("%s", "Unknow socket family!");
            this->init_flag_ = false;
            return SockRet::EINIT;
    }
    this->family_ = family;
    this->address_ = address;
    this->init_flag_ = true;
    return SockRet::SUCCESS;
}

bool SockAddress::AddrChecek()
{
    return this->init_flag_;
}

}//namespace sock end
