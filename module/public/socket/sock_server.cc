#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>

#include "sock_log.h"
#include "sock_server.h"

#define SOCK_DEFAULT_LISTEN_CACHE (100)

namespace sock {

SockServer::SockServer(SockFamily family, unsigned short int port)
            :family_(family), port_(port)
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
    this->address_.clear();
    this->listen_fd_ = NULL;
    this->listen_cache_ = SOCK_DEFAULT_LISTEN_CACHE;
    this->mempool_ = rm::RMMemPool::getInstance();
    this->init_flag_ = true;
}

SockServer::SockServer(SockFamily family, char* address, unsigned short int port)
                    :family_(family), port_(port)
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
    this->address_ = address;
    this->listen_fd_ = NULL;
    this->listen_cache_ = SOCK_DEFAULT_LISTEN_CACHE;
    this->mempool_ = rm::RMMemPool::getInstance();
    this->init_flag_ = true;
}

SockServer::SockServer(SockFamily family, char* address)
                    :family_(family)
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
    this->address_ = address;
    this->listen_fd_ = NULL;
    this->listen_cache_ = SOCK_DEFAULT_LISTEN_CACHE;
    this->mempool_ = rm::RMMemPool::getInstance();
    this->init_flag_ = true;
}

SockServer::~SockServer()
{
    if( this->init_flag_ ) {
        if (this->listen_fd_) {
            this->listen_fd_->Close();
            this->mempool_->Free<SockFD>(this->listen_fd_);
        }
    }
}

SockRet SockServer::Bind()
{
    SockRet ret;
    if (!this->init_flag_) {
        SOCK_ERROR("%s", "Not initialized")
        return SockRet::EINIT;
    }
    if ((ret = _socket()) != SockRet::SUCCESS) {
        return ret;
    }
    if ((ret = _bind()) != SockRet::SUCCESS) {
        this->listen_fd_->Close();
        this->mempool_->Free<SockFD>(this->listen_fd_);
        this->listen_fd_ = NULL;
        return ret;
    }
    if ((ret = _listen()) != SockRet::SUCCESS) {
        this->listen_fd_->Close();
        this->mempool_->Free<SockFD>(this->listen_fd_);
        this->listen_fd_ = NULL;
        return ret;
    }
    return SockRet::SUCCESS;
}

SockRet SockServer::Accept(SockFD* sockfd)
{
    if (!this->init_flag_) {
        SOCK_ERROR("%s", "Not initialized")
        return SockRet::ERROR;
    }
    if (this->domain_ == SOCK_DGRAM) {
        SOCK_ERROR("%s", "UDP socket no need be accepted");
        return SockRet::ERROR;
    }
    return SockRet::SUCCESS;
}

SockRet SockServer::_socket()
{
    int temp_errno;
    int sockfd = 0;
    sockfd = socket(this->domain_, this->type_, 0);
    if (sockfd < 0) {
        temp_errno = errno;
        SOCK_ERROR("%s%s", "Create socket error, ", strerror(temp_errno));
        return _errno2ret(temp_errno);
    }
    if (!this->listen_fd_) {
        this->listen_fd_ = this->mempool_->Malloc<SockFD>(sockfd);
    } else {
        this->listen_fd_ = this->mempool_->Reset<SockFD>(this->listen_fd_, sockfd);
    }
    if (!this->listen_fd_) {
        return SockRet::EMALLOC;
    }
    return SockRet::SUCCESS;
}

SockRet SockServer::_bind()
{
    int ret;
    int temp_errno;
    if (this->domain_ == AF_LOCAL) {
        struct sockaddr_un addr;
        addr.sun_family = AF_LOCAL;
        strcpy(addr.sun_path, this->address_.c_str());
        unlink(this->address_.c_str());
        ret = bind(this->listen_fd_->getFD(), (struct sockaddr*)&addr, sizeof(struct sockaddr));
        if (ret != 0) {
            temp_errno = errno;
            SOCK_ERROR("%s%s", "bind socket error, ", strerror(temp_errno));
            unlink(this->address_.c_str());
            return _errno2ret(temp_errno);
        }
    } else if (this->domain_ == AF_INET) {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        if (this->address_.empty()) {
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
        } else {
            addr.sin_addr.s_addr = htonl(inet_addr(this->address_.c_str()));
        }
        addr.sin_port = htons(this->port_);

        ret = bind(this->listen_fd_->getFD(), (struct sockaddr*)&addr, sizeof(struct sockaddr));
        if (ret != 0) {
            temp_errno = errno;
            SOCK_ERROR("%s%s", "bind socket error, ", strerror(temp_errno));
            return _errno2ret(temp_errno);
        }
    } else if (this->domain_ == AF_INET6) {
        struct sockaddr_in6 addr;
        addr.sin6_family = AF_INET6;
        if (this->address_.empty()) {
            addr.sin6_addr = IN6ADDR_ANY_INIT;
        } else {
          ret = inet_pton(AF_INET6, this->address_.c_str(), &(addr.sin6_addr));
          if (ret < 0) {
            temp_errno = errno;
            SOCK_ERROR("Address is not in presentation format[%s]", this->address_.c_str());
            return _errno2ret(temp_errno);
          }
        }
        addr.sin6_port = htons(this->port_);

        ret = bind(this->listen_fd_->getFD(), (struct sockaddr*)&addr, sizeof(struct sockaddr));
        if (ret != 0) {
            temp_errno = errno;
            SOCK_ERROR("%s%s", "bind socket error, ", strerror(temp_errno));
            return _errno2ret(temp_errno);
        }

    } else {

    }
    return SockRet::SUCCESS;
}

SockRet SockServer::_listen()
{
    int temp_errno;
    int ret = listen(this->listen_fd_->getFD(), this->listen_cache_);
    if (ret) {
        temp_errno = errno;
        SOCK_ERROR("%s%s", "Listen socket error, ", strerror(temp_errno));
        return _errno2ret(temp_errno);
    }
    return SockRet::SUCCESS;
}

} //namespace sock end
