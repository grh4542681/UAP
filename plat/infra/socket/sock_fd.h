#ifndef __SOCK_FD_H__
#define __SOCK_FD_H__

#include <netinet/in.h>

#include "time/vtime.h"
#include "mempool.h"
#include "io_fd.h"

#include "sock_log.h"
#include "sock_return.h"
#include "sock_address.h"

namespace sock{

/**
* @brief - Socker file descriptor operator class.
*/
class SockFD : public io::FD {
public:
    friend class SockServer;
    friend class SockClient;

    SockFD();
    SockFD(unsigned int fd, bool auto_close = false);
    SockFD(SockFD& other);
    ~SockFD();

    SockRet SetFD(unsigned int fd, bool auto_close = false);
    io::FD* Clone();

    //for multicast attrubit
    SockRet SetMcastJoin(const char* mcast_addr);
    SockRet SetMcastJoin(const char* mcast_addr, const char* if_name, unsigned int if_index);
    SockRet SetMcastLeave(const char* mcast_addr);
    SockRet SetMcastInterface(const char* if_name, unsigned int if_index);
    SockRet SetMcastTTL(unsigned int ttl);
    SockRet SetMcastloop(bool flag);

    SockRet SetSendBlock(util::time::Time* overtime);
    SockRet SetRecvBlock(util::time::Time* overtime);
    SockRet SetNonBlock();

    bool isClientFD();
    bool isServerFD();
    bool isAcceptFD();
    bool isMulitcastFD();

    void Close();
    size_t Write(const void* data, size_t datalen);
    size_t Read(void* data, size_t datalen);
    size_t Send(SockAddress* dest, const void* data, size_t datalen);
    size_t Recv(SockAddress* orig, void* data, size_t datalen);
    size_t SendFD(unsigned int fd);
    size_t RecvFD(unsigned int *fd);
    
private:

//    bool init_flag_;            ///< init flag.
//    bool auto_close_;           ///< auto close fd flag.
//    unsigned int fd_;           ///< socket file descriptor.
    mempool::MemPool* mempool_; ///< memory pool interface.
    SockAddress orig;           ///< source address.
    SockAddress dest;           ///< destination address.

    /**
    * @brief _errno2ret - Convert errno to SockRet.
    *
    * @param [ierrno] - errno.
    *
    * @returns  SockRet.
    */
    static SockRet _errno2ret(int ierrno){
        switch (ierrno) {
            case 0:
                return SockRet::SUCCESS;
            case EACCES:
                return SockRet::SOCK_EACCES;
            case EAFNOSUPPORT:
                return SockRet::SOCK_EAFNOSUPPORT;
            case EINVAL:
                return SockRet::SOCK_EINVAL;
            case EMFILE:
                return SockRet::SOCK_EMFILE;
            case ENFILE:
                return SockRet::SOCK_ENFILE;
            case ENOBUFS:
                return SockRet::SOCK_ENOBUFS;
            case ENOMEM:
                return SockRet::SOCK_ENOMEM;
            case EPROTONOSUPPORT:
                return SockRet::SOCK_EPROTONOSUPPORT;
            case EADDRINUSE:
                return SockRet::SOCK_EADDRINUSE;
            case EBADF:
                return SockRet::SOCK_EBADF;
            case ENOTSOCK:
                return SockRet::SOCK_ENOTSOCK;
            case EOPNOTSUPP:
                return SockRet::SOCK_EOPNOTSUPP;
            case EAGAIN:
                return SockRet::SOCK_EAGAIN;
            default:
                SOCK_ERROR("Unknow errno[%d]", ierrno);
                return SockRet::EUNKOWNERRNO;
        }   
    }

    int _close();

    size_t _send(struct sockaddr* dest, const void* data, size_t datalen, void* ctrldata, size_t ctrldatalen, int flags);
    size_t _recv(struct sockaddr* orig, void* data, size_t datalen, void* ctrldata, size_t ctrldatalen, int flags);
};

}//namespace socket end

#endif
