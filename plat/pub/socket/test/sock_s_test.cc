#include "sock_common.h"
#include "sock_address.h"
#include "sock_fd.h"
#include "sock_server.h"
#include <unistd.h>

int main()
{
    char buff[1024];
    std::string unixfile = "sock.sock";
    sock::SockServer s = sock::SockServer(sock::SockFamily::TCP_LOCAL, unixfile.c_str());
    //sock::SockServer s = sock::SockServer(sock::SockFamily::TCP_INET6, 60004);
    //sock::SockServer s = sock::SockServer(sock::SockFamily::TCP_INET4, 60004);
    //sock::SockServer s = sock::SockServer(sock::SockFamily::MULTICAST_INET4, "228.0.0.1", 60005);
    //sock::SockServer s = sock::SockServer(sock::SockFamily::UDP_INET6, 60005);
    s.Bind();
    //sock::SockFD* fd = s.getSockFD();
    //if(!fd){
    //    printf("-**--\n");
    //}
    while(1){
        sock::SockFD fd;
        s.Accept(&fd);
        sleep(1);
        sock::SockAddress addr;
        struct timeval overtime = {3,0};
        //fd.setRecvBlock(&overtime);
        memset(buff, 0x00, sizeof(buff));
        //int ret = fd->Recv(&addr, buff, sizeof(buff));
        int ret = fd.Recv(buff, sizeof(buff));
        printf("ret[%d][%s][%s]\n", ret, buff, addr.getAddr().c_str());
    }
    return 0;
}
