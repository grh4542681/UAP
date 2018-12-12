#ifndef __SOCK_FD_H__
#define __SOCK_FD_H__

#include <netinet/in.h>

#include "rm_mempool.h"
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

    SockRet setSendBlock(struct timeval* overtime);
    SockRet setSendNonBlock();
    SockRet setRecvBlock(struct timeval* overtime);
    SockRet setRecvNonBlock();

    bool isClientFD();
    bool isServerFD();
    bool isAcceptFD();

    void Close();
    size_t Send(const void* data, size_t datalen);
    size_t Recv(void* data, size_t datalen);
    size_t SendFD(struct sockaddr_in* dest, unsigned int fd, int flags);
    size_t RecvFD(struct sockaddr_in* orig, unsigned int *fd, int flags);
    
private:

    bool init_flag_;
    unsigned int fd_;
    rm::RMMemPool* mempool_;
    SockAddress orig;
    SockAddress dest;

    int _close();

    size_t _send(struct sockaddr_in* dest, const void* data, size_t datalen, void* ctrldata, size_t ctrldatalen, int flags);
    size_t _recv(struct sockaddr_in* orig, void* data, size_t datalen, void* ctrldata, size_t ctrldatalen, int flags);
};

}//namespace socket end

#endif
