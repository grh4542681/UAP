#include "sock_common.h"
#include "sock_address.h"
#include "sock_fd.h"
#include "sock_client.h"
#include <unistd.h>

int main()
{
    sock::SockFD* fd = NULL;
    std::string unixfile = "sock.sock";
    sock::SockClient s = sock::SockClient(sock::SockFamily::TCP_LOCAL, unixfile.c_str());
    //sock::SockClient s = sock::SockClient(sock::SockFamily::TCP_INET6, 60004);
    //sock::SockClient s = sock::SockClient(sock::SockFamily::TCP_INET4, 60004);
    fd = s.Connect();
    fd->Send("hello world", 12);
    fd->Close();
    return 0;
}
