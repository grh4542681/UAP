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
{
    this->mempool_ = pub::MemPool::getInstance();
    if (!this->mempool_) {
        this->init_flag_ = false;
        return;
    }
    this->s_address_ = this->mempool_->Malloc<SockAddress>(family, port);
    if (!this->s_address_->AddrCheck()) {
        this->init_flag_ = false;
        return;
    }
    this->listen_fd_ = NULL;
    this->listen_cache_ = SOCK_DEFAULT_LISTEN_CACHE;
    this->init_flag_ = true;
}

SockServer::SockServer(SockFamily family, const char* address, unsigned short int port)
{
    this->mempool_ = pub::MemPool::getInstance();
    if (!this->mempool_) {
        this->init_flag_ = false;
        return;
    }
    this->s_address_ = this->mempool_->Malloc<SockAddress>(family, address, port);
    if (!this->s_address_->AddrCheck()) {
        this->init_flag_ = false;
        return;
    }
    this->listen_fd_ = NULL;
    this->listen_cache_ = SOCK_DEFAULT_LISTEN_CACHE;
    this->init_flag_ = true;
}

SockServer::SockServer(SockFamily family, const char* address)
{
    this->mempool_ = pub::MemPool::getInstance();
    if (!this->mempool_) {
        this->init_flag_ = false;
        return;
    }
    this->s_address_ = this->mempool_->Malloc<SockAddress>(family, address);
    if (!this->s_address_->AddrCheck()) {
        this->init_flag_ = false;
        return;
    }
    this->listen_fd_ = NULL;
    this->listen_cache_ = SOCK_DEFAULT_LISTEN_CACHE;
    this->init_flag_ = true;
}

SockServer::SockServer(SockAddress* address)
{
    this->mempool_ = pub::MemPool::getInstance();
    if (!this->mempool_) {
        this->init_flag_ = false;
        return;
    }
    this->s_address_ = this->mempool_->Malloc<SockAddress>(*address);
    if (!this->s_address_->AddrCheck()) {
        this->init_flag_ = false;
        return;
    }
    this->listen_fd_ = NULL;
    this->listen_cache_ = SOCK_DEFAULT_LISTEN_CACHE;
    this->init_flag_ = true;
}

SockServer::~SockServer()
{
    if (this->listen_fd_) {
        this->listen_fd_->Close();
        this->mempool_->Free<SockFD>(this->listen_fd_);
    }
    if (this->s_address_) {
        this->mempool_->Free<SockAddress>(this->s_address_);
    }
}

SockFD* SockServer::getSockFD()
{
    if (!this->init_flag_) {
        SOCK_ERROR("%s", "Not initialized");
        return NULL;
    }
    return this->listen_fd_;
}

SockRet SockServer::Bind()
{
    SockRet ret;
    if (!this->init_flag_) {
        SOCK_ERROR("%s", "Not initialized");
        return SockRet::EINIT;
    }
    if ((ret = _socket()) != SockRet::SUCCESS) {
        if (this->listen_fd_) {
            this->listen_fd_->Close();
            this->mempool_->Free<SockFD>(this->listen_fd_);
            this->listen_fd_ = NULL;
        }
        return ret;
    }
    if ((ret = _bind()) != SockRet::SUCCESS) {
        this->listen_fd_->Close();
        this->mempool_->Free<SockFD>(this->listen_fd_);
        this->listen_fd_ = NULL;
        return ret;
    }
    if (this->s_address_->type_ == SOCK_STREAM) {
        if ((ret = _listen()) != SockRet::SUCCESS) {
            this->listen_fd_->Close();
            this->mempool_->Free<SockFD>(this->listen_fd_);
            this->listen_fd_ = NULL;
            return ret;
        }
    } else if (this->s_address_->type_ == SOCK_DGRAM) {
        //if multicast server and given multicast group, add socket to this multicast group
        if (this->s_address_->isMulticast() && !this->s_address_->address_.empty()) {
            if ((ret = this->listen_fd_->setMcastJoin(this->s_address_->address_.c_str())) != SockRet::SUCCESS) {
                this->listen_fd_->Close();
                this->mempool_->Free<SockFD>(this->listen_fd_);
                this->listen_fd_ = NULL;
                return ret;
            }
        }
    }
    return SockRet::SUCCESS;
}

SockRet SockServer::Accept(SockFD* sockfd)
{
    if (!this->init_flag_) {
        SOCK_ERROR("%s", "Not initialized");
        return SockRet::ERROR;
    }
    if (this->s_address_->type_ == SOCK_DGRAM) {
        SOCK_ERROR("%s", "UDP socket no need be accepted");
        return SockRet::ERROR;
    }
    int temp_errno;
    int acpt_fd = -1;
    switch(this->s_address_->domain_) {
        case AF_LOCAL:
            struct sockaddr_un un_addr;
            socklen_t un_addrlen;
            acpt_fd = accept(this->listen_fd_->getFD(), (struct sockaddr*)&un_addr, &un_addrlen);
            if (acpt_fd < 0) {
                temp_errno = errno;
                SOCK_ERROR("%s%s", "Accept socket error, ", strerror(temp_errno));
                return _errno2ret(temp_errno);
            }
            sockfd->setFD(acpt_fd);
            sockfd->orig = SockAddress(*(this->s_address_));
            sockfd->dest = SockAddress(this->s_address_->family_, un_addr.sun_path);
            break;
        case AF_INET:
            struct sockaddr_in in_addr;
            socklen_t in_addrlen;
            acpt_fd = accept(this->listen_fd_->getFD(), (struct sockaddr*)&in_addr, &in_addrlen);
            if (acpt_fd < 0) {
                temp_errno = errno;
                SOCK_ERROR("%s%s", "Accept socket error, ", strerror(temp_errno));
                return _errno2ret(temp_errno);
            }
            sockfd->setFD(acpt_fd);
            sockfd->orig = SockAddress(*(this->s_address_));
            sockfd->dest = SockAddress(this->s_address_->family_, inet_ntoa(in_addr.sin_addr), in_addr.sin_port);
            break;
        case AF_INET6:
            struct sockaddr_in6 in6_addr;
            char c_in6_addr[SOCK_ADDRESS_MAX_LEN];
            socklen_t in6_addrlen;
            acpt_fd = accept(this->listen_fd_->getFD(), (struct sockaddr*)&in6_addr, &in6_addrlen);
            if (acpt_fd < 0) {
                temp_errno = errno;
                SOCK_ERROR("%s%s", "Accept socket error, ", strerror(temp_errno));
                return _errno2ret(temp_errno);
            }
            if (!inet_ntop(AF_INET6, &in6_addr.sin6_addr, c_in6_addr, SOCK_ADDRESS_MAX_LEN)) {
                temp_errno = errno;
                SOCK_ERROR("%s%s", "Accept socket error, inet_ntop error", strerror(temp_errno));
                return _errno2ret(temp_errno);
            }
            sockfd->setFD(acpt_fd);
            sockfd->orig = SockAddress(*(this->s_address_));
            sockfd->dest = SockAddress(this->s_address_->family_, c_in6_addr, in6_addr.sin6_port);
            break;
        default:
            SOCK_ERROR("Unkown destnation family[%d]", this->s_address_->type_);
            break;
    }
    return SockRet::SUCCESS;
}

SockRet SockServer::_socket()
{
    int temp_errno;
    int sockfd = 0;
    int on = 1;
    sockfd = socket(this->s_address_->domain_, this->s_address_->type_, 0);
    if (sockfd < 0) {
        temp_errno = errno;
        SOCK_ERROR("%s%s", "Create socket error, ", strerror(temp_errno));
        return _errno2ret(temp_errno);
    }
    if ((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0) {
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
    this->listen_fd_->orig = SockAddress(*(this->s_address_));
    return SockRet::SUCCESS;
}

SockRet SockServer::_bind()
{
    int ret;
    int temp_errno;
    if (this->s_address_->domain_ == AF_LOCAL) {
        struct sockaddr_un addr;
        addr.sun_family = AF_LOCAL;
        strcpy(addr.sun_path, this->s_address_->address_.c_str());
        unlink(this->s_address_->address_.c_str());
        ret = bind(this->listen_fd_->getFD(), (struct sockaddr*)&addr, sizeof(struct sockaddr));
        if (ret != 0) {
            temp_errno = errno;
            SOCK_ERROR("%s%s", "bind socket error, ", strerror(temp_errno));
            unlink(this->s_address_->address_.c_str());
            return _errno2ret(temp_errno);
        }
    } else if (this->s_address_->domain_ == AF_INET) {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        if (this->s_address_->address_.empty() || this->s_address_->isMulticast()) {
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
        } else {
            addr.sin_addr.s_addr = htonl(inet_addr(this->s_address_->address_.c_str()));
        }
        addr.sin_port = htons(this->s_address_->port_);

        ret = bind(this->listen_fd_->getFD(), (struct sockaddr*)&addr, sizeof(struct sockaddr));
        if (ret != 0) {
            temp_errno = errno;
            SOCK_ERROR("%s%s", "bind socket error, ", strerror(temp_errno));
            return _errno2ret(temp_errno);
        }
    } else if (this->s_address_->domain_ == AF_INET6 || this->s_address_->isMulticast()) {
        struct sockaddr_in6 addr;
        addr.sin6_family = AF_INET6;
        if (this->s_address_->address_.empty()) {
            addr.sin6_addr = in6addr_any;
        } else {
          ret = inet_pton(AF_INET6, this->s_address_->address_.c_str(), &(addr.sin6_addr));
          if (ret < 0) {
            temp_errno = errno;
            SOCK_ERROR("Address is not in presentation format[%s]", this->s_address_->address_.c_str());
            return _errno2ret(temp_errno);
          }
        }
        addr.sin6_port = htons(this->s_address_->port_);

        ret = bind(this->listen_fd_->getFD(), (struct sockaddr*)&addr, sizeof(struct sockaddr_in6));
        if (ret != 0) {
            temp_errno = errno;
            SOCK_ERROR("%s%s", "bind socket error, ", strerror(temp_errno));
            return _errno2ret(temp_errno);
        }
    } else {
        SOCK_ERROR("%s", "Unknow domain for socket");
        return SockRet::ERROR;
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
