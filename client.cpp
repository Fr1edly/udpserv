#include "client.h"

namespace Net{
    Client::Client(int port, std::string ip):
    port(port),
    ipaddr(ip),
    clientsock(0),
    info{0},
    infolen(sizeof(info)){}

    void Client::init(){
        info.sin_family = AF_INET;
        info.sin_port = htons(port);
        info.sin_addr.s_addr = inet_addr(ipaddr.c_str());

        printf("Create socket\n");
        assert(!((clientsock = socket(AF_INET, SOCK_DGRAM, 0)) == SO_ERROR) && "Couldn't create socket");

        printf("Client started at: %s:%d", inet_ntoa(info.sin_addr), htons(info.sin_port));
    }

    void Client::connect(){
        init();

        for(;;){
            send();
            receive();
            proccesse();
        }
    }

    void Client::send(){
        printf("Enter a message: ");
        std::getline(std::cin, message);
        if((sendto(clientsock, message.c_str(), message.size(), 0, (struct sockaddr*)&info, infolen)) == SO_ERROR){
            printf("send() failed..\n");
            exit(EXIT_FAILURE);
        }
    }
    void Client::receive(){
        if((recvlen = recvfrom(clientsock, buffer, SIZE, 0,(struct sockaddr*)&info, &infolen)) == SO_ERROR){
            printf("recv() failed..\n");
            exit(EXIT_FAILURE);
       }
    }
    void Client::proccesse(){
        printf("packet from:%s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
        for(size_t i =0; i<recvlen; i++)
            printf("%c", buffer[i]);
    }
    Client::~Client(){

    }

}