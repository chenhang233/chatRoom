#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <thread>
#include <arpa/inet.h>

#define IP_ARR_LEN 16

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


