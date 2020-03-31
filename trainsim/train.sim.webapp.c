//
// Created by abc on 31/03/2020.
//

#include "train.sim.webapp.h"
#include <stdio.h>
#include <winsock2.h>

//Addapted from https://www.binarytides.com/winsock-socket-programming-tutorial/



int createServer(int port, char*(*datahandler)()){
    WSADATA wsa;
    SOCKET listenersocket;
    struct sockaddr_in server , client;
    int c;
    int errcode = 0;
    printf("Initialising Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
        printf("Failed. Error Code : %d",WSAGetLastError());
        return WSAGetLastError();
    }
    else{
        printf("Initialised.\n");
    }

    if((listenersocket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET){
        printf("Could not create socket : %d" , WSAGetLastError());
        return WSAGetLastError();
    }else{
        printf("Socket created.\n");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( port );
    //Bind
    if( bind(listenersocket ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d\n" , WSAGetLastError());
        return WSAGetLastError();
    }
    else{
        printf("Bind socket done on port %i\n", port);
    }

    int running = 0;
    while(running == 0){
        //Listen to incoming connections
        listen(listenersocket , 3);

        //Accept and incoming connection
        printf("Waiting for incoming connections...\n");

        c = sizeof(struct sockaddr_in);
        SOCKET clientsocket;
        clientsocket = accept(listenersocket , (struct sockaddr *)&client, &c);
        if (clientsocket == INVALID_SOCKET)
        {
            printf("accept failed with error code : %d" , WSAGetLastError());
            errcode = WSAGetLastError();
            running = 1;
        }else{
            char *msgheader = calloc(sizeof(char), 500);
            char *msgcontent;
            char *msg;
            printf("Connection accepted\n");
            //Return data......
            msgcontent = datahandler();
            strcpy (msgheader, "HTTP/1.1 200 OK\nContent-Type: text/html; charset=UTF-8\ncontent-length: ");
            char strlength[10];
            //printf("%d", strlen(msgcontent));
            sprintf(strlength, "%d", strlen(msgcontent));
            //printf("bla");
            msg = calloc(sizeof(char), (strlen(msgheader) + strlen(msgcontent) + strlen(strlength)));
            strcpy(msg, msgheader);
            strcat(msg, strlength);
            strcat(msg, "\n\n");
            strcat(msg, msgcontent);
            //printf("bla2");
            printf("-----Returning data-------\n%s\n-----end of data-------\n\n", msg);

            send(clientsocket , msg , strlen(msg) , 0);
            free(msgheader);
            free(msgcontent);
            free(msg);
        }
        closesocket(clientsocket);
    }
    //cleanup
    closesocket(listenersocket);
    WSACleanup();
    //Error codes are found here: https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2
    return errcode;
}

char* restDataHandler(){
    char *text = calloc(sizeof(char), 100000);
    strcpy(text, "{ Hi:'Here have some json..'}");
    return text;
}

int restServerStart(int port){
    printf("restServerStart init");
    return createServer(port, &restDataHandler);
}

char* StaticDataHandler(){
    char *text = calloc(sizeof(char), 100000);
    printf("Settings..");
    strcpy(text, "<html><body><h1>Hello There!</h1><p>This is a staic page, any kinda changes on the page is done using javascript and ajax calls..</body></html>");
    printf("Returning data..");
    return text;
}

int staticServerStart(int port){
    printf("staticServerStart init");
    return createServer(port, &StaticDataHandler);
}