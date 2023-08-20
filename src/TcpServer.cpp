#include "TcpServer.h"

TcpServer::TcpServer() {
   this->sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8888);
    bind(this->sock, (struct sockaddr *)&addr, sizeof(addr));
    this->addr = addr;
}

TcpServer::TcpServer(int port)
{
    //  AF_INET: IPv4 网络协议 
    // SOCK_STREAM: TCP流
    this->sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    bind(this->sock, (struct sockaddr *)&addr, sizeof(addr));
    this->addr = addr;
    this->addr_len = sizeof(this->addr);
}

TcpServer::~TcpServer()
{
}