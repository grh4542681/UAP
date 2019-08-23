#include "message_server.h"

namespace message {

MessageServer::MessageServer()
{

}

MessageServer::~MessageServer()
{

}

MessageRet MessageServer::Run()
{
    char buff[1024];
    server_ = sock::SockServer(message::GetMessageServerAddress());
    printf("addr %s\n",server_.s_address_.getAddr().c_str());
    server_.Bind();
    printf("fd %d\n", server_.GetSockFD().GetFD());
    while(1) {
        sock::SockFD afd;
        sock::SockAddress addr;
        server_.Accept(&afd);
        memset(buff,0,sizeof(buff));
        int ret = afd.Recv(&addr, buff, sizeof(buff));
        printf("ret[%d][%s][%s]\n", ret, buff, addr.getAddr().c_str());
        afd.Send(NULL, buff, strlen(buff));
        sleep(2);
        afd.Close();
    }
}

}
