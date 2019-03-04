#ifndef __SOCK_CLIENT_H__
#define __SOCK_CLIENT_H__

#include "mempool.h"
#include "sock_return.h"
#include "sock_common.h"
#include "sock_address.h"
#include "sock_fd.h"

namespace sock{

class SockClient {
public:

    SockClient(SockFamily family, const char* address, unsigned short int port);
    SockClient(SockFamily family, const char* address);
    SockClient(SockAddress* address);
    ~SockClient();

    SockFD* getSockFD();
    SockRet setTimeout(struct timeval* overtime);
    SockFD* Connect();

private:
    SockClient(const SockClient&);
    const SockClient& operator=(const SockClient&);

    bool init_flag_;
    mempool::MemPool* mempool_;
    SockAddress* s_address_;
    SockFD* conn_fd_;

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
            default:
                return SockRet::EUNKOWNERRNO;
        }
    }

    SockRet _socket();
    SockRet _connect();

};

}// namespace sock end


#endif
