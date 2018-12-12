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
    s.Bind();
    while(1){
        sock::SockFD fd;
        s.Accept(&fd);
        memset(buff, 0x00, sizeof(buff));
        fd.Recv(buff, sizeof(buff));
        printf("%s\n", buff);
        fd.Close();
    }
    return 0;
}
