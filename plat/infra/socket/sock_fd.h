#ifndef __SOCK_FD_H__
#define __SOCK_FD_H__

#include <netinet/in.h>

#include "mempool.h"
#include "sock_log.h"
#include "sock_return.h"
#include "sock_address.h"

namespace sock{

class SockFD{
public:
    friend class SockServer;
    friend class SockClient;

    SockFD();
    SockFD(unsigned int fd);
    ~SockFD();

    unsigned int getFD();
    SockRet setFD(unsigned int fd);

    //for multicast attrubit
    SockRet setMcastJoin(const char* mcast_addr);
    SockRet setMcastJoin(const char* mcast_addr, const char* if_name, unsigned int if_index);
    SockRet setMcastLeave(const char* mcast_addr);
    SockRet setMcastInterface(const char* if_name, unsigned int if_index);
    SockRet setMcastTTL(unsigned int ttl);
    SockRet setMcastloop(bool flag);

    SockRet setSendBlock(struct timeval* overtime);
    SockRet setRecvBlock(struct timeval* overtime);
    SockRet setNonBlock();

    bool isClientFD();
    bool isServerFD();
    bool isAcceptFD();
    bool isMulitcastFD();

    void Close();
    size_t Send(const void* data, size_t datalen);
    size_t Recv(void* data, size_t datalen);
    size_t Send(SockAddress* dest, const void* data, size_t datalen);
    size_t Recv(SockAddress* orig, void* data, size_t datalen);
    size_t SendFD(unsigned int fd);
    size_t RecvFD(unsigned int *fd);
    
private:

    bool init_flag_;
    unsigned int fd_;
    mempool::MemPool* mempool_;
    SockAddress orig;
    SockAddress dest;

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
