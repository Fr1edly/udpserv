#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <assert.h>

#define SIZE 1024

namespace Net{
    class Client{
    private:
        int clientsock;
        std::string ipaddr;
        int port;
        char buffer[SIZE];
        std::string message;
        struct sockaddr_in info;
        socklen_t infolen, recvlen;
    
    public:
        Client(int, std::string);
        ~Client();
    public:
        void connect();
        void stop();

    private:
        void init();
        void receive();
        void proccesse();
        void send();
    };
}