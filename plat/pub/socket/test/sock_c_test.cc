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
    //sock::SockClient s = sock::SockClient(sock::SockFamily::MULTICAST_INET4, "228.0.0.1", 60005);
    //sock::SockClient s = sock::SockClient(sock::SockFamily::UDP_INET6, NULL, 60005);
    fd = s.Connect();
    if(!fd){
        printf("------\n");
        return 0;
    }
    fd->Send("hello world", 12);
    sleep(5);
    fd->Close();
    return 0;
}
