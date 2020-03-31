#include <stdio.h>
#include "train.sim.webapp.h"

int main() {
    printf("Welcome to the train sim!\n");
    /*
     *  1.   Programmet starter
        2.    simulering som er hardcoded indlæses
        3.    simulering starts I sin egen tråd
        4.    Port åbnes så connections kan komme ind på port 5000
        5.    Programmet køre for evigt, eller indtil at det lukkes ned via webinterface command.
     * */
    init_socket();
    return 0;
}
