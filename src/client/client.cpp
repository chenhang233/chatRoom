#include "client.h"

#define BUFFER_LEN 1024

ClientServer::ClientServer():TcpServer() {

}


void handleRecv(void *p) {
    ClientServer* c = (ClientServer*)p;
    while (true)
    {
        char* data;
        recv(c->sock,data,BUFFER_LEN,0);
        cout << data << endl;
    }
    cout << "handleRecv END" << endl;
}

void ClientServer::Run() {
   cout << "client running ..." << endl;
   while (true)
   {
        // printf("Please enter IP address of the server: ");
        // scanf("%s", this->server_ip);
        // printf("Please enter port number of the server: ");
        // scanf("%d", &this->server_port);
        // getchar();
        this->addr.sin_port = htons(this->server_port);
        this->addr.sin_addr.s_addr = inet_addr(this->server_ip);
        if (connect(this->sock, (struct sockaddr *)&this->addr, sizeof(this->addr)) < 0)
        {
            cout << "connect error" << endl;
            continue;
        }
        break;
   }
    char state[10] = {0};
    if (recv(this->sock,state,sizeof(state),0) < 0) {
        cout << "recv ERROR" << endl;
        return;
    }
    if (strcmp(state,"OK")) {
        cout << "The chatroom is already full!" << endl;
        return;
    }
    cout << "server OK" << endl;
    cout << "Please enter your name: " << endl;
    while (true)
    {
        getline(cin,this->name);
        if (cin.eof()) {
            cout << "Please enter your name: " << endl;
            cin.clear();
            cin.get();
            continue;
        }
        break;
    }
    const char* s = this->name.c_str();
    send(this->sock,s , strlen(s), 0);
    thread th(handleRecv,this);
    th.detach();
    string  str;
    cout << "Please enter your message" << endl;
    while (true)
    {
        getline(cin,str);
        const char* c_str = str.c_str();
        if (send(this->sock,c_str,strlen(c_str),0) == -1) {
            return;
        };
    }

    cout << "exit room" << endl;
    return;
}