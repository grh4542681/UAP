#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include "sock_log.h"
#include "sock_fd.h"

namespace sock{

//public


/**
* @brief SockFD - Default consturctor
*/
SockFD::SockFD(){
    this->mempool_ = pub::MemPool::getInstance();
    this->fd_ = 0;
    this->init_flag_ = false;
}

/**
* @brief SockFD - Constructor
*
* @param [fd] - File descriptor
*/
SockFD::SockFD(unsigned int fd){
    int temp_errno = 0;
    struct stat fd_stat;
    if (fstat(fd, &fd_stat)) {
        temp_errno = errno;
        SOCK_ERROR("%s", strerror(temp_errno));
        this->init_flag_ = false;
    }
    if (!S_ISSOCK(fd_stat.st_mode)) {
        SOCK_ERROR("fd[%d] not a socket fd", fd);
        this->init_flag_ = false;
    }

    this->mempool_ = pub::MemPool::getInstance();
    this->fd_ = fd;
    this->init_flag_ = true;
}

/**
* @brief ~SockFD - Destructor.
*/
SockFD::~SockFD(){
    if (this->init_flag_) {
        _close();
    }
}

/**
* @brief setFD - Set or reset file descriptors.
*
* @param [fd] - File descriptor
*
* @returns  SockRet
*/
SockRet SockFD::setFD(unsigned int fd)
{
    if (this->fd_ > 0) {
        _close();
        this->fd_ = 0;
    }
    int temp_errno = 0;
    struct stat fd_stat;
    if (fstat(fd, &fd_stat)) {
        temp_errno = errno;
        SOCK_ERROR("%s", strerror(temp_errno));
        this->init_flag_ = false;
    }
    if (!S_ISSOCK(fd_stat.st_mode)) {
        SOCK_ERROR("fd[%d] not a socket fd", fd);
        this->init_flag_ = false;
    }
    this->fd_ = fd;
    this->init_flag_ = true;
    return SockRet::SUCCESS;
}

/**
* @brief getFD - Get file descriptor
*
* @returns  File descriptor
*/
unsigned int SockFD::getFD()
{
    if (this->init_flag_) {
        return this->fd_;
    } else {
        return (-1);
    }
}

SockRet SockFD::setMcastJoin(const char* mcast_addr)
{
    return SockRet::SUCCESS;
}

SockRet SockFD::setMcastJoin(const char* mcast_addr, const char* mcast_if_addr)
{
    return SockRet::SUCCESS;
}

SockRet SockFD::setMcastLeave(const char* mcast_addr)
{
    return SockRet::SUCCESS;
}

SockRet SockFD::setMcastLeave(const char* mcast_addr, const char* mcast_if_addr)
{
    return SockRet::SUCCESS;
}

SockRet SockFD::setMcastInterface(const char* mcast_if_addr)
{
    return SockRet::SUCCESS;
}

SockRet SockFD::setMcastTTL(int ttl)
{
    return SockRet::SUCCESS;
}

SockRet SockFD::setMcastloop(bool flag)
{
    return SockRet::SUCCESS;
}

/**
* @brief setSendBlock - Set Blocked when send msg
*
* @param [overtime] - Over time, if NULL, it will be blocked all time.
*
* @returns  SockRet
*/
SockRet SockFD::setSendBlock(struct timeval* overtime)
{
    int temp_errno = 0;
    struct timeval otime;
    int flag = 0;
    flag = fcntl(this->fd_, F_GETFL);
    if (flag < 0) {
        temp_errno = errno;
        SOCK_ERROR("%s", strerror(temp_errno));
        return _errno2ret(temp_errno);
    }
    if (flag & O_NONBLOCK) {
        flag &= (~O_NONBLOCK);
        if (fcntl(this->fd_, F_SETFL, &flag) < 0) {
            temp_errno = errno;
            SOCK_ERROR("%s", strerror(temp_errno));
            return _errno2ret(temp_errno);
        }
    }
    if (overtime) {
        memcpy(&otime, overtime, sizeof(struct timeval));
    } else {
        otime.tv_sec = 0;
        otime.tv_usec = 0;
    }
    if (setsockopt(this->fd_, SOL_SOCKET, SO_SNDTIMEO, &otime, sizeof(struct timeval)) < 0) {
        temp_errno = errno;
        SOCK_ERROR("%s", strerror(temp_errno));
        return _errno2ret(temp_errno);
    }
    return SockRet::SUCCESS;
}

/**
* @brief setRecvBlock - Set blocked when recv msg
*
* @param [overtime] - Over time, if NULL, it will be blocked all the time
*
* @returns  SockRet
*/
SockRet SockFD::setRecvBlock(struct timeval* overtime)
{
    int temp_errno = 0;
    struct timeval otime;
    int flag = 0;
    flag = fcntl(this->fd_, F_GETFL);
    if (flag < 0) {
        temp_errno = errno;
        SOCK_ERROR("%s", strerror(temp_errno));
        return _errno2ret(temp_errno);
    }
    if (flag & O_NONBLOCK) {
        flag &= (~O_NONBLOCK);
        if (fcntl(this->fd_, F_SETFL, &flag) < 0) {
            temp_errno = errno;
            SOCK_ERROR("%s", strerror(temp_errno));
            return _errno2ret(temp_errno);
        }
    }
    if (overtime) {
        memcpy(&otime, overtime, sizeof(struct timeval));
    } else {
        otime.tv_sec = 0;
        otime.tv_usec = 0;
    }
    if (setsockopt(this->fd_, SOL_SOCKET, SO_RCVTIMEO, &otime, sizeof(struct timeval)) < 0) {
        temp_errno = errno;
        SOCK_ERROR("%s", strerror(temp_errno));
        return _errno2ret(temp_errno);
    }
    return SockRet::SUCCESS;
}

/**
* @brief setNonBlock - Set recv and send msg non-block
*
* @returns  SockRet
*/
SockRet SockFD::setNonBlock()
{
    int temp_errno = 0;
    int flag = 0;
    flag = fcntl(this->fd_, F_GETFL);
    if (flag < 0) {
        temp_errno = errno;
        SOCK_ERROR("%s", strerror(temp_errno));
        return _errno2ret(temp_errno);
    }
    if (!(flag & O_NONBLOCK)) {
        flag |= O_NONBLOCK;
        if (fcntl(this->fd_, F_SETFL, &flag) < 0) {
            temp_errno = errno;
            SOCK_ERROR("%s", strerror(temp_errno));
            return _errno2ret(temp_errno);
        }
    }
    return SockRet::SUCCESS;
}

/**
* @brief isClientFD - Check this FD was created by client.
*
* @returns  true or false
*/
bool SockFD::isClientFD()
{
    if (!this->orig.AddrCheck() && this->dest.AddrCheck()) {
        return true;
    }
    return false;
}

/**
* @brief isServerFD - Check this FD was created by server.
*
* @returns  true or false
*/
bool SockFD::isServerFD()
{
    if (this->orig.AddrCheck() && !this->dest.AddrCheck()) {
        return true;
    }
    return false;
}

/**
* @brief isAcceptFD - Check this FD was created by accept.
*
* @returns  true or false
*/
bool SockFD::isAcceptFD()
{
    if (this->orig.AddrCheck() && this->dest.AddrCheck()) {
        return true;
    }
    return false;
}

/**
* @brief Close - Close FD
*/
void SockFD::Close()
{
    if (this->init_flag_) {
        _close();
    }
    this->init_flag_ = false;
}

/**
* @brief Send - Send message
*
* @param [data] - Data pointer that will be sended.
* @param [datalen] - Length of data.
*
* @returns  SockRet or send length
*/
size_t SockFD::Send(const void* data, size_t datalen)
{
    SockAddress* tmp = isClientFD() ? &(this->dest) : &(this->orig);
    if (tmp->type_ == SOCK_DGRAM) {
        SockAddress* dest = &(this->dest);
        if (!dest->AddrCheck()) {
            SOCK_ERROR("UDP send need destnation address");
            return (-1);
        }
        struct sockaddr dest_addr;
        memset(&dest_addr, 0x00, sizeof(struct sockaddr));
        if (dest->ToSockaddr(&dest_addr) != SockRet::SUCCESS) {
            SOCK_ERROR("Convert address error");
            return (-1);
        }
        return _send(&dest_addr, data, datalen, NULL, 0, 0);
    } else {
        return _send(NULL, data, datalen, NULL, 0, 0);
    }
}

/**
* @brief Recv - Recv message 
*
* @param [data] - Pointer that Space for receiving data
* @param [datalen] - Space length
*
* @returns  SockRet or recv length.
*/
size_t SockFD::Recv(void* data, size_t datalen)
{
    return _recv(NULL, data, datalen, NULL, 0, 0);
}

/**
* @brief Send - Send message,Generally used for UDP.
*               If not UDP, dest will not be used.
*
* @param [dest] - Destination address,if NULL same to other functions.
* @param [data] - Data pointer that will be sended.
* @param [datalen] - Data length
*
* @returns  SockRet or send length
*/
size_t SockFD::Send(SockAddress* dest, const void* data, size_t datalen)
{
    SockAddress* tmp = isClientFD() ? &(this->dest) : &(this->orig);
    if (tmp->type_ == SOCK_DGRAM) {
        if (!dest) {
            dest = &(this->dest);
        }
        if (!dest->AddrCheck()) {
            SOCK_ERROR("UDP send need destnation address");
            return (-1);
        }
        struct sockaddr dest_addr;
        memset(&dest_addr, 0x00, sizeof(struct sockaddr));
        if (dest->ToSockaddr(&dest_addr) != SockRet::SUCCESS) {
            SOCK_ERROR("Convert address error");
            return (-1);
        }
        return _send(&dest_addr, data, datalen, NULL, 0, 0);
    } else {
        return _send(NULL, data, datalen, NULL, 0, 0);
    }
}

/**
* @brief Recv - Recv message,Generally used for UDP.
*               If not UDP, orig will not be used.
*
* @param [orig] - Source address.Allowed to be NULL.
* @param [data] - Pointer that Space for receiving data
* @param [datalen] - Space length
*
* @returns  SockRet or recv length.
*/
size_t SockFD::Recv(SockAddress* orig, void* data, size_t datalen)
{
    int ret = 0;

    SockAddress* tmp = isClientFD() ? &(this->dest) : &(this->orig);
    if (tmp->type_ == SOCK_DGRAM) {
        switch(tmp->domain_){
            case AF_LOCAL:
                struct sockaddr_un un_addr;
                ret = _recv((struct sockaddr*)&un_addr, data, datalen, NULL, 0, 0);
                orig->_init(tmp->family_, un_addr.sun_path);
                break;
            case AF_INET:
                struct sockaddr_in in_addr;
                ret = _recv((struct sockaddr*)&in_addr, data, datalen, NULL, 0, 0);
                orig->_init(tmp->family_, inet_ntoa(in_addr.sin_addr), in_addr.sin_port);
                break;
            case AF_INET6:
                char c_in6_addr[SOCK_ADDRESS_MAX_LEN];
                struct sockaddr_in6 in6_addr;
                ret = _recv((struct sockaddr*)&in6_addr, data, datalen, NULL, 0, 0);
               if (!inet_ntop(AF_INET6, &in6_addr.sin6_addr, c_in6_addr, SOCK_ADDRESS_MAX_LEN)) {
                    int temp_errno = errno;
                    SOCK_ERROR("%s%s", "Accept socket error, inet_ntop error", strerror(temp_errno));
                    return (-1);
               } 
               orig->_init(tmp->family_, c_in6_addr, in6_addr.sin6_port);
               break;
            default:
                SOCK_ERROR("Unknow socket family");
                return (-1);
        }
        return ret;
    } else {
        return _recv(NULL, data, datalen, NULL, 0, 0);
    }
}

/**
* @brief SendFD - Send a valid file descriptor to another process
*
* @param [fd] - File descriptor
*
* @returns  SockRet or send length
*/
size_t SockFD::SendFD(unsigned int fd)
{
    char ctrlmsg[CMSG_SPACE(sizeof(int))];

    if (!this->init_flag_) {
        SOCK_ERROR("%s", "fd not inited");
        return (-1);
    }

    struct cmsghdr* pcmsg = reinterpret_cast<struct cmsghdr*>(ctrlmsg);
    pcmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;
    *((int*)CMSG_DATA(pcmsg)) = fd;

    return _send(NULL, NULL, 0, ctrlmsg, sizeof(ctrlmsg), 0);
}

/**
* @brief RecvFD - Recv a Valid file descriptor from other process.
*
* @param [fd] - File descriptor
*
* @returns  SockRet or send length
*/
size_t SockFD::RecvFD(unsigned int* fd)
{
    int ret = 0;
    char ctrlmsg[CMSG_SPACE(sizeof(int))];

    if (!this->init_flag_) {
        SOCK_ERROR("%s", "fd not inited");
        return (-1);
    }

    struct cmsghdr* pcmsg = reinterpret_cast<struct cmsghdr*>(ctrlmsg);
    pcmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;

    ret = _recv(NULL, NULL, 0, ctrlmsg, sizeof(ctrlmsg), 0);

    *fd = *((int*)CMSG_DATA(pcmsg));

    return ret;
}

//private
/**
* @brief _close - close fd
*
* @returns  0 or -1
*/
int SockFD::_close()
{
    SOCK_DEBUG("sockfd[%d] closed", this->fd_);
    return close(this->fd_);
}

size_t SockFD::_send(struct sockaddr* dest, const void* data, size_t datalen, void* ctrldata, size_t ctrldatalen, int flags)
{
    int ret = 0;
    int temp_errno;
    if (!data && !ctrldata) {
        SOCK_ERROR("%s", "No data needs to be sent");
        return (-1);
    }
    struct msghdr msg;
    memset(&msg, 0x00, sizeof(struct msghdr));

    //fill addr
    struct sockaddr dest_addr;
    memset(&dest_addr, 0x00, sizeof(struct sockaddr));
    if (dest) {
        memcpy(&dest_addr, dest, sizeof(struct sockaddr));
        msg.msg_name = &dest_addr;
        msg.msg_namelen = sizeof(struct sockaddr);
    } else {
        msg.msg_name = NULL;
        msg.msg_namelen = 0;
    }

    //fill data
    char fakebuff[1];
    char* buff = NULL;
    size_t bufflen = 0;
    struct iovec iov[1];
    bool buff_free_flag = false;

    if (data) {
        buff = static_cast<char*>(this->mempool_->Malloc(datalen));
        if (!buff) {
            SOCK_ERROR("%s", "Malloc error");
            return (-1);
        }
        memset(buff, 0x00, datalen);
        memcpy(buff, data, datalen);
        bufflen = datalen;
        buff_free_flag = true;
    } else {
        buff = fakebuff;
        bufflen = 1;
        buff_free_flag = false;
    }
    iov[0].iov_base = buff;
    iov[0].iov_len = bufflen;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    //fill ctrl data
    if (ctrldata) {
        msg.msg_control = ctrldata;
        msg.msg_controllen = ctrldatalen;
    }

    ret = sendmsg(this->fd_, &msg, flags);
    if (ret == 0) {
        ret = (int)SockRet::SOCK_LINKDOWN;
    } else if (ret < 0) {
        temp_errno = errno;
        ret = (int)_errno2ret(temp_errno);
    }
    if (buff_free_flag) {
        this->mempool_->Free(buff);
    }
    return ret;
}

size_t SockFD::_recv(struct sockaddr* orig, void* data, size_t datalen, void* ctrldata, size_t ctrldatalen, int flags)
{
    int ret = 0;
    int temp_errno;
    struct msghdr msg;
    char fakebuff[1];
    char* buff = NULL;
    size_t bufflen = 0;
    struct iovec iov[1];

    if (!data && !ctrldata) {
        SOCK_ERROR("%s", "No data buffer, bad arguments");
        return (-1);
    }

    memset(&msg, 0x00, sizeof(struct msghdr));
    if (data) {
        buff = static_cast<char*>(this->mempool_->Malloc(datalen));
        if (!buff) {
            SOCK_ERROR("%s", "Malloc error");
            return (-1);
        }
        memset(buff, 0x00, datalen);
        bufflen = datalen;
    } else {
        buff = fakebuff;
        bufflen = 1;
    }
    iov[0].iov_base = buff;
    iov[0].iov_len = bufflen;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    //fill ctrl data
    if (ctrldata) {
        msg.msg_control = ctrldata;
        msg.msg_controllen = ctrldatalen;
    }

    ret = recvmsg(this->fd_, &msg, flags);
    if (ret == 0) {
        return (size_t)SockRet::SOCK_LINKDOWN;
    } else if (ret < 0) {
        temp_errno = errno;
        return (size_t)_errno2ret(temp_errno);
    }

    //fill data
    if (data) {
        memcpy(data, buff, datalen);
        this->mempool_->Free(buff);
    }

    //fill addr
    struct sockaddr dest_addr;
    memset(&dest_addr, 0x00, sizeof(struct sockaddr));
    if (orig) {
        memcpy(orig, msg.msg_name, msg.msg_namelen);
    }

    return ret;
}

}//namespace socket end
