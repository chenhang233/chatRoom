#include "server.h"

ChatServer::ChatServer(int port,int max_client_num):TcpServer(port) {
    listen(this->sock,max_client_num);
    this->max_client_num = max_client_num;
    cout << "listen port:" << port << " max_client_num: " << max_client_num << endl;
}

ChatServer::~ChatServer() {

}

void ChatServer::Run() {
    cout << "ChatServer running ..." << endl;
    while (true)
    {
        int client_sock = accept(this->sock, NULL, NULL);
        if (client_sock == -1) {
            cout << "accept" << endl;
            continue;
        }
        cout << "accept client: " << client_sock << endl;
        if (this->current_client_num >= this->max_client_num) {
            send(client_sock, "MAX ERROR", strlen("MAX ERROR"), 0);
            shutdown(client_sock, SHUT_RDWR);
            continue;
        } else {
            send(client_sock,"OK",strlen("OK"),0);
        }
        thread th(Chat,this,&client_sock);
    }
}


void Chat(void * p,int* client_sock) {
    ChatServer *s = (ChatServer *)p;
    char m[100]; 
    struct sockaddr_in addr_client;
    int recv_num = recvfrom(*client_sock,m,sizeof(m),0,(struct sockaddr *)&addr_client, (socklen_t *)&s->addr_len);
    if (recv_num < 0) {
        cout << "recvfrom error" << endl;
        return;
    }
    m[recv_num] = '\0';
    cout << m << endl;
    cout << addr_client.sin_addr.s_addr << endl;
    cout << addr_client.sin_port << endl;
}

void Send(void *) {

}