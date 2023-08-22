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
        queue<Message> messages,history_msgs;
        map<int,Client> idMaps;
        void Run();
        ChatServer(int port,int max_client_num);
        ~ChatServer();
};