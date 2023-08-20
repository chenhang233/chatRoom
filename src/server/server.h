#pragma once
#include "../TcpServer.h"
#include <queue>
#include <map>

#define IP_ARR_LEN 4

void Chat(void *,int*);
void Send(void *);


struct Client
{
    unsigned char ip_arr[IP_ARR_LEN];
    int port;
    int id;
    string name;
    int ack;
};

struct Message {
    int sequence;
    int id;
    string name;
    string body;
};


class ChatServer:public TcpServer {
    public:
        int current_client_num;
        int max_client_num;
        queue<Message> massages;
        map<int,bool> idMaps;
        vector<pthread_t> threadArr; 
        pthread_t chat_thread;
        void Run();
        ChatServer(int port,int max_client_num);
        ~ChatServer();
};