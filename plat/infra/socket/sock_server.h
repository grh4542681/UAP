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

    SockRet _socket();
    SockRet _bind();
    SockRet _listen();

};

}//namespace sock end

#endif
