#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <assert.h>

#define SIZE 1024

namespace Net{
    class Server{
    private:
        int servsock;
        std::string ipaddr;
        int port;
        char buffer[SIZE];
        std::string message;
        struct sockaddr_in info;
        socklen_t infolen, recvlen;
    
    public:
        Server(int , std::string);
        ~Server();
    public:
        void start();
        void stop();

    private:
        void init();
        void receive();
        void proccesse();
        void send();
    };
}