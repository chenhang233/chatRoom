main: Server Client

Server: TcpServer.cpp server/main.cpp server/server.cpp 
	g++ TcpServer.cpp server/main.cpp server/server.cpp -std=c++11  -o Server -lpthread

Client: client/main.cpp client/client.cpp TcpServer.cpp
	g++ client/main.cpp client/client.cpp TcpServer.cpp -std=c++11 -o Client -lpthread

.PHONY: clean
clean:
	rm Server Client