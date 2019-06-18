#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>

#include "sock_log.h"
#include "sock_client.h"

namespace sock{

SockClient::SockClient(SockFamily family, const char* address, unsigned short int port)
{
    this->mempool_ = mempool::MemPool::getInstance();
    if (!this->mempool_) {
        this->init_flag_ = false;
        return;
    }   
    this->s_address_ = this->mempool_->Malloc<SockAddress>(family, address, port);
    if (!this->s_address_->AddrCheck()) {
        this->init_flag_ = false;
        return;
    }   
    this->conn_fd_ = NULL;
    this->init_flag_ = true;

}

SockClient::SockClient(SockFamily family, const char* address)
{
    this->mempool_ = mempool::MemPool::getInstance();
    if (!this->mempool_) {
        this->init_flag_ = false;
        return;
    }   
    this->s_address_ = this->mempool_->Malloc<SockAddress>(family, address);
    if (!this->s_address_->AddrCheck()) {
        this->init_flag_ = false;
        return;
    }   
    this->conn_fd_ = NULL;
    this->init_flag_ = true;

}

SockClient::SockClient(SockAddress* address)
{
    this->mempool_ = mempool::MemPool::getInstance();
    if (!this->mempool_) {
        this->init_flag_ = false;
        return;
    }   
    this->s_address_ = this->mempool_->Malloc<SockAddress>(*address);
    if (!this->s_address_->AddrCheck()) {
        this->init_flag_ = false;
        return;
    }   
    this->conn_fd_ = NULL;
    this->init_flag_ = true;

}

SockClient::~SockClient()
{
    if (this->conn_fd_) {
        this->conn_fd_->Close();
        this->mempool_->Free<SockFD>(this->conn_fd_);
    }   
    if (this->s_address_) {
        this->mempool_->Free<SockAddress>(this->s_address_);
    }
}

SockFD* SockClient::getSockFD()
{
    if (!this->init_flag_) {
        SOCK_ERROR("%s", "Not initialized")
        return NULL;
    }
    return this->conn_fd_;
}

SockRet SockClient::SetTimeout(struct timeval* overtime)
{
    SOCK_DEBUG("Not support now");
    return SockRet::SUCCESS;
}

SockFD* SockClient::Connect()
{
    SockRet ret;
    if (!this->init_flag_) {
        SOCK_ERROR("%s", "Not initialized")
        return NULL;
    }
    if ((ret = _socket()) != SockRet::SUCCESS) {
        if (this->conn_fd_) {
            this->conn_fd_->Close();
            this->mempool_->Free<SockFD>(this->conn_fd_);
            this->conn_fd_ = NULL;
        }
    }
    if (this->s_address_->type_ == SOCK_DGRAM) {
        SOCK_DEBUG("%s", "UDP no need connect");
    } else {
        if ((ret = _connect()) != SockRet::SUCCESS) {
            this->conn_fd_->Close();
            this->mempool_->Free<SockFD>(this->conn_fd_);
            this->conn_fd_ = NULL;
        }
    }
    return this->conn_fd_;
}

//private
SockRet SockClient::_socket()
{
    int temp_errno;
    int sockfd = 0;
    sockfd = socket(this->s_address_->domain_, this->s_address_->type_, 0);
    if (sockfd < 0) {
        temp_errno = errno;
        SOCK_ERROR("%s%s", "Create socket error, ", strerror(temp_errno));
        return _errno2ret(temp_errno);
    }
    if (!this->conn_fd_) {
        this->conn_fd_ = this->mempool_->Malloc<SockFD>(sockfd);
    } else {
        this->conn_fd_ = this->mempool_->Reset<SockFD>(this->conn_fd_, sockfd);                                                                                                                               
    }
    if (!this->conn_fd_) {
        return SockRet::EMALLOC;
    }
    this->conn_fd_->dest = SockAddress(*(this->s_address_));
    return SockRet::SUCCESS;
}

SockRet SockClient::_connect()
{
    int ret;
    int temp_errno;
    if (this->s_address_->domain_ == AF_LOCAL) {
        struct sockaddr_un addr;
        addr.sun_family = AF_LOCAL;
        strcpy(addr.sun_path, this->s_address_->address_.c_str());
        ret = connect(this->conn_fd_->GetFD(), (struct sockaddr*)&addr, sizeof(struct sockaddr));
        if (ret != 0) {
            temp_errno = errno;
            SOCK_ERROR("%s%s", "connect socket error, ", strerror(temp_errno));
            unlink(this->s_address_->address_.c_str());
            return _errno2ret(temp_errno);
        }
    } else if (this->s_address_->domain_ == AF_INET) {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        if (this->s_address_->address_.empty()) {
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
        } else {
            addr.sin_addr.s_addr = htonl(inet_addr(this->s_address_->address_.c_str()));
        }
        addr.sin_port = htons(this->s_address_->port_);

        ret = connect(this->conn_fd_->GetFD(), (struct sockaddr*)&addr, sizeof(struct sockaddr));
        if (ret != 0) {
            temp_errno = errno;
            SOCK_ERROR("%s%s", "connect socket error, ", strerror(temp_errno));
            return _errno2ret(temp_errno);
        }
    } else if (this->s_address_->domain_ == AF_INET6) {
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

        ret = connect(this->conn_fd_->GetFD(), (struct sockaddr*)&addr, sizeof(struct sockaddr_in6));
        if (ret != 0) {
            temp_errno = errno;
            SOCK_ERROR("%s%s", "connect socket error, ", strerror(temp_errno));
            return _errno2ret(temp_errno);
        }
    } else {
        SOCK_ERROR("%s", "Unknow domain for socket");
        return SockRet::ERROR;
    }
    return SockRet::SUCCESS;

}

}
