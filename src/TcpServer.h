#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <thread>

using namespace std;

class TcpServer
{
private:
public:
    int sock;
    struct sockaddr_in addr;
    int addr_len;
    TcpServer(int port);
    TcpServer();
    ~TcpServer();
    virtual void Run() = 0;
};


