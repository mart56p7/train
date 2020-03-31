//
// Created by abc on 31/03/2020.
//

#include "train.sim.webapp.h"
#include <stdio.h>
#include <winsock2.h>
WSADATA wsa;
SOCKET s;

int init_socket(){
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return WSAGetLastError();
    }

    printf("Initialised.\n");


    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
        return WSAGetLastError();
    }

    printf("Socket created.\n");
    return 0;
}