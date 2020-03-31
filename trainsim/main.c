#include <stdio.h>
#include "train.sim.webapp.h"
#include <windows.h>

DWORD WINAPI StaticServerRunner() {
    // Do stuff.  This will be the first function called on the new thread.
    // When this function returns, the thread goes away.  See MSDN for more details.
    staticServerStart(8001);
    return 0;
}


int main() {
    printf("Welcome to the train sim!\n");
    /*
     *  1.   Programmet starter
        2.    simulering som er hardcoded indlæses
        3.    simulering starts I sin egen tråd
        4.    Port åbnes så connections kan komme ind på port 5000
        5.    Programmet køre for evigt, eller indtil at det lukkes ned via webinterface command.
     * */

    //https://stackoverflow.com/questions/1981459/using-threads-in-c-on-windows-simple-example
    //https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread
    HANDLE thread = CreateThread(NULL, 0, StaticServerRunner, NULL, 0, NULL);
    //we wait to create a lock so the program doesnt end
    restServerStart(8002);
    return 0;
}
