#pragma once
#include "../TcpServer.h"
#include <queue>
#include <map>
#include <random>

#define MSG_BUFFER 1024

void Chat(void *,int);
void handleMessage(void *);
int RandInt();


struct Client
{
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
        map<int,Client> idMaps;
        vector<pthread_t> threadArr; 
        pthread_t chat_thread;
        void Run();
        ChatServer(int port,int max_client_num);
        ~ChatServer();
};