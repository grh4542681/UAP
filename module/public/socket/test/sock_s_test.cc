#include "sock_common.h"
#include "sock_address.h"
#include "sock_fd.h"
#include "sock_server.h"
#include <unistd.h>

int main()
{
    std::string unixfile = "sock.sock";
    //sock::SockServer s = sock::SockServer(sock::SockFamily::TCP_LOCAL, unixfile.c_str());
    sock::SockServer s = sock::SockServer(sock::SockFamily::TCP_INET6, 60001);
    s.Bind();
    sleep(20);
    return 0;
}
