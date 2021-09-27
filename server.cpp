#include "server.h"

namespace Net{
    Server::Server(int port, std::string ip):
    port(port),
    ipaddr(ip),
    servsock(0),
    info{0},
    infolen(sizeof(info)){}

    void Server::init(){
        info.sin_family = AF_INET;
        info.sin_port = htons(port);
        info.sin_addr.s_addr = inet_addr(ipaddr.c_str());

        printf("Create socket\n");
        assert(!((servsock = socket(AF_INET, SOCK_DGRAM, 0)) == SO_ERROR) && "Couldn't create socket");

        printf("Bind socket\n");
        assert(!(bind(servsock, (struct sockaddr*)&info, infolen)) && "Couldn't bind socket");

        printf("Server started at: %s:%d\n", inet_ntoa(info.sin_addr), htons(info.sin_port));
    }

    void Server::start(){
        init();

        for(;;){
            receive();
            proccesse();
            send();
        }
    }

    void Server::receive(){
        if(!((recvlen = recvfrom(servsock, buffer, SIZE, 0,(struct sockaddr*)&info, &infolen))) == SO_ERROR){
            printf("recv() failed..\n");
            exit(EXIT_FAILURE);
       }
    }
    void Server::proccesse(){
        printf("packet from:%s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
        for(size_t i =0; i<recvlen; i++)
            printf("%c", buffer[i]);
        printf("\n");
    }
    void Server::send(){
        if((sendto(servsock, buffer, recvlen, 0, (struct sockaddr*)&info, sizeof(info))) == SO_ERROR){
            printf("send() failed..\n");
            exit(EXIT_FAILURE);
        }
    }

    Server::~Server(){
    }

}