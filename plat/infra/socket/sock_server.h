#ifndef __SOCK_SERVER_H__
#define __SOCK_SERVER_H__

#include <memory>
#include <string.h>

#include "mempool.h"
#include "sock_return.h"
#include "sock_common.h"
#include "sock_address.h"
#include "sock_fd.h"

namespace sock{

/**
* @brief - Socket server class.
*/
class SockServer {
public:
    
    SockServer(SockFamily family, unsigned short int port);
    SockServer(SockFamily family, const char* address, unsigned short int port);
    SockServer(SockFamily family, const char* address);
    SockServer(SockAddress* address);
    ~SockServer();

    /**
    * @brief getSockFD - Get current socket file descriptor.
    *
    * @returns  SockFD pointer.
    */
    SockFD* getSockFD();

    /**
    * @brief Bind - bind
    *
    * @returns  SockRet.
    */
    SockRet Bind();
    /**
    * @brief Accept - accept.
    *
    * @param [sockfd] - Output arguments SockFd pointer.
    *
    * @returns  SockRet.
    */
    SockRet Accept(SockFD* sockfd);

private:
    SockServer(const SockServer&);
    const SockServer& operator=(const SockServer&);

    bool init_flag_;
    mempool::MemPool* mempool_;
    SockAddress* s_address_;
    unsigned int listen_cache_;
    SockFD* listen_fd_;

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
    SockRet _bind();
    SockRet _listen();

};

}//namespace sock end

#endif
