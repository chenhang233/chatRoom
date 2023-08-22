#pragma once
#include "../TcpServer.h"


class ClientServer:public TcpServer {
    public:
        char server_ip[IP_ARR_LEN] = {'1','2','7','.','0','.','0','.','1'};
        int server_port = 8000;
        string name;
        ClientServer();
        void Run();
};