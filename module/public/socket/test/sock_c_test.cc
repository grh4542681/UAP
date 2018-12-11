#include "sock_common.h"
#include "sock_address.h"
#include "sock_fd.h"
#include "sock_client.h"
#include <unistd.h>

int main()
{
    sock::SockFD fd;
    std::string unixfile = "sock.sock";
    //sock::SockClient s = sock::SockClient(sock::SockFamily::TCP_LOCAL, unixfile.c_str());
    sock::SockClient s = sock::SockClient(sock::SockFamily::TCP_INET6, 60004);
    s.Connect(&fd);
    fd.Send("hello world", 12);
    fd.Close();
    return 0;
}
