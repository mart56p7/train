//
// Created by abc on 31/03/2020.
//

#include "train.sim.webapp.h"
#include <stdio.h>
#include <winsock2.h>

//Addapted from https://www.binarytides.com/winsock-socket-programming-tutorial/
int serverStart(int port){
    WSADATA wsa;
    SOCKET listenersocket;
    struct sockaddr_in server , client;
    int c;
    int errcode = 0;
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return WSAGetLastError();
    }

    printf("Initialised.\n");


    if((listenersocket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
        return WSAGetLastError();
    }

    printf("Socket created.\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( port );

    //Bind
    if( bind(listenersocket ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        return WSAGetLastError();
    }
    else{
        puts("Bind done");
    }

    int running = 0;
    while(running == 0){
        //Listen to incoming connections
        listen(listenersocket , 3);

        //Accept and incoming connection
        puts("Waiting for incoming connections...");

        c = sizeof(struct sockaddr_in);
        SOCKET clientsocket;
        clientsocket = accept(listenersocket , (struct sockaddr *)&client, &c);
        if (clientsocket == INVALID_SOCKET)
        {
            printf("accept failed with error code : %d" , WSAGetLastError());
            errcode = WSAGetLastError();
            running = 1;
        }else{
            puts("Connection accepted");
            //Return data......
            char *message;
            message = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=UTF-8\ncontent-length: 0\n";
            send(clientsocket , message , strlen(message) , 0);
        }
        closesocket(clientsocket);
    }
    //cleanup
    closesocket(listenersocket);
    WSACleanup();
    //Error codes are found here: https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2
    return errcode;
}