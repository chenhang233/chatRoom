#include "server.h"

ChatServer::ChatServer(int port,int max_client_num):TcpServer(port) {
    listen(this->sock,max_client_num);
    this->max_client_num = max_client_num;
    this->current_client_num = 0;
    cout << "listen port:" << port << 
    " max_client_num: " << max_client_num 
    << "current_client_num: " << this->current_client_num << endl;
}

ChatServer::~ChatServer() {

}

void ChatServer::Run() {
    cout << "ChatServer running ..." << endl;
    thread handle(handleMessage,this);
    handle.detach();
    while (true)
    {
        cout << "loop ing..." << endl;
        int client_sock = accept(this->sock, NULL, NULL);
        if (client_sock == -1) {
            cout << "accept ERROR" << endl;
            continue;
        }
        cout << "client_sock: " << client_sock << endl;
        if (this->current_client_num >= this->max_client_num) {
            send(client_sock, "MAX ERROR", strlen("MAX ERROR"), 0);
            shutdown(client_sock, SHUT_RDWR);
            continue;
        } else {
            send(client_sock,"OK",strlen("OK"),0);
        }
        this->current_client_num++;
        thread th(Chat,this,client_sock);
        th.detach();
    }
    cout << "ChatServer end ..." << endl;
}


void Chat(void * p,int client_sock) {
    cout << "Chat running ..." << endl;
    ChatServer *s = (ChatServer *)p;
    char m[100];
    int recv_num = recv(client_sock,m,sizeof(m),0);
    if (recv_num < 0) {
        cout << "recvfrom name error" << endl;
        return;
    }
    m[recv_num] = '\0';
    cout << m << endl;
    Client c;
    c.name = string(m);
    c.ack = 0; 
    c.id = client_sock;
    while (true)
    {
        auto search = s->idMaps.find(c.id);
        if (search != s->idMaps.end()) {
            c.id++;
            continue; 
        }
        break;
    }
    s->idMaps[c.id] = c;
    char message[MSG_BUFFER];
    while (true)
    {        
        recv_num = recv(client_sock,message,sizeof(message),0);  
        if (recv_num > 0) {
            message[recv_num] = '\0';
            Message next_m;
            next_m.body = string(message);
            next_m.name = c.name;
            next_m.id = c.id;
            int next_size = s->messages.size() + 1;
            next_m.sequence = next_size;
            s->messages.push(next_m);
            s->history_msgs.push(next_m);
        }
    }
    cout << "Chat end" << endl;
}

void handleMessage(void * p) {
  cout << "handleMessage running ..." << endl;
  ChatServer *s = (ChatServer *)p;
  while (true)
  {
    while (!s->messages.empty())
    {
        Message m = s->messages.front();
        s->messages.pop();
        map<int, Client>::iterator it;
        int send_id = 0;
        for ( it= s->idMaps.begin(); it != s->idMaps.end(); it++)
        {
            auto c = it->second;
            if (c.id != m.id) {
                const char* str = m.body.c_str();
                send(c.id,str,sizeof(str),0);
            } else {
                send_id = c.id;
            }
            c.ack++;
        }
        send(send_id,"OK",strlen("OK"),0);  
    }
  }
    cout << "handleMessage end ..." << endl;
}

int RandInt() {
    random_device rd;
    mt19937 gen(rd()); 
    uniform_int_distribution<> dis(1, 10000);
    return dis(gen); 
}

