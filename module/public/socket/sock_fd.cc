#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>

#include "sock_log.h"
#include "sock_fd.h"

namespace sock{

SockFD::SockFD(){
    this->mempool_ = rm::RMMemPool::getInstance();
    this->fd_ = -1;
    this->init_flag_ = false;
}

SockFD::SockFD(unsigned int fd){
    int temp_errno = 0;
    int flag;
    socklen_t flaglen;
    if ((getsockopt(fd, SOL_SOCKET, SO_ACCEPTCONN, &flag, &flaglen))) {
        temp_errno = errno;
        if (temp_errno == EBADF) {
            SOCK_ERROR("%s", strerror(temp_errno));
            this->init_flag_ = false;
        }
    } else {
        if (flag) {
            this->init_flag_ = true;
            this->fd_ = fd;
            this->mempool_ = rm::RMMemPool::getInstance();
        } else {
            SOCK_ERROR("sock fd [%d] no be listened!", fd);
            this->init_flag_ = false;
        }
    }
}

SockFD::~SockFD(){
    if (this->init_flag_) {
        _close();
    }
}

SockRet SockFD::setFD(unsigned int fd)
{
    int temp_errno = 0;
    int flag;
    socklen_t flaglen;
    if (this->fd_ > 0) {
        _close();
        this->fd_ = -1;
    }
    if ((getsockopt(fd, SOL_SOCKET, SO_ACCEPTCONN, &flag, &flaglen))) {
        temp_errno = errno;
        if (temp_errno == EBADF) {
            SOCK_ERROR("%s", strerror(temp_errno));
            this->init_flag_ = false;
        }
    } else {
        if (flag) {
            this->init_flag_ = true;
            this->fd_ = fd;
        } else {
            SOCK_ERROR("sock fd [%d] no be listened!", fd);
            this->init_flag_ = false;
        }
    }
}

unsigned int SockFD::getFD()
{
    if (this->init_flag_) {
        return this->fd_;
    } else {
        return (0);
    }
}

void SockFD::Close()
{
    if (this->init_flag_) {
        _close();
    }
    this->init_flag_ = false;
}

size_t SockFD::Send(void* data, size_t datalen)
{
    return _send(NULL, data, datalen, NULL, 0, 0);
}

size_t SockFD::Recv(void* data, size_t datalen)
{
    return _recv(NULL, data, datalen, NULL, 0, 0);
}

size_t SockFD::SendFD(struct sockaddr_in* dest, unsigned int fd, int flags)
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

    return _send(dest, NULL, 0, ctrlmsg, sizeof(ctrlmsg), flags);
}

size_t SockFD::RecvFD(struct sockaddr_in* dest, unsigned int* fd, int flags)
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

    ret = _recv(dest, NULL, 0, ctrlmsg, sizeof(ctrlmsg), flags);

    *fd = *((int*)CMSG_DATA(pcmsg));

    return ret;
}

//private
int SockFD::_close()
{
    return close(this->fd_);
}

size_t SockFD::_send(struct sockaddr_in* dest, void* data, size_t datalen, void* ctrldata, size_t ctrldatalen, int flags)
{
    int ret = 0;
    if (!data && !ctrldata) {
        SOCK_ERROR("%s", "No data needs to be sent");
        return (-1);
    }
    struct msghdr msg;
    memset(&msg, 0x00, sizeof(struct msghdr));

    //fill addr
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0x00, sizeof(struct sockaddr_in));
    if (dest) {
        memcpy(&dest_addr, dest, sizeof(struct sockaddr_in));
        msg.msg_name = &dest_addr;
        msg.msg_namelen = sizeof(struct sockaddr_in);
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
    if (buff_free_flag) {
        this->mempool_->Free(buff);
    }
    return ret;
}

size_t SockFD::_recv(struct sockaddr_in* orig, void* data, size_t datalen, void* ctrldata, size_t ctrldatalen, int flags)
{
    int ret = 0;
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

    //fill data
    if (data) {
        memcpy(data, buff, datalen);
        this->mempool_->Free(buff);
    }

    //fill addr
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0x00, sizeof(struct sockaddr_in));
    if (orig) {
        memcpy(orig, msg.msg_name, msg.msg_namelen);
    }

    return ret;
}

}//namespace socket end
