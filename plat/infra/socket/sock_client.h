#ifndef __SOCK_CLIENT_H__
#define __SOCK_CLIENT_H__

#include "mempool.h"
#include "sock_return.h"
#include "sock_common.h"
#include "sock_address.h"
#include "sock_fd.h"

namespace sock{

/**
* @brief - Socket client class.
*/
class SockClient {
public:

    SockClient(SockFamily family, const char* address, unsigned short int port);
    SockClient(SockFamily family, const char* address);
    SockClient(SockAddress* address);
    ~SockClient();

    /**
    * @brief getSockFD - Get current socket file descriptor.
    *
    * @returns  SockFD pointer.
    */
    SockFD* getSockFD();
    /**
    * @brief SetTimeout - Set connect over time.
    *
    * @param [overtime] - Over time.
    *
    * @returns  SockRet.
    */
    SockRet SetTimeout(struct timeval* overtime);
    /**
    * @brief Connect - connect.
    *
    * @returns  SockFD pointer.
    */
    SockFD* Connect();

private:
    SockClient(const SockClient&);
    const SockClient& operator=(const SockClient&);

    bool init_flag_;
    mempool::MemPool* mempool_;
    SockAddress* s_address_;
    SockFD* conn_fd_;

    SockRet _socket();
    SockRet _connect();

};

}// namespace sock end


#endif
