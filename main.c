#include <stdio.h>
#include "motrain.lib.h"

void stuff(){
    printTrains();
}

int main() {
    printf("Hello, World!\n");
    Train a = 1;
    Train b = 2;
    Train c = 3;
    Train d = 4;
    Train e = 5;
    Train f = 6;
    addTrain(a);
    addTrain(b);
    addTrain(c);
    addTrain(d);
    addTrain(e);
    printTrains();
    addTrain(e);
    addTrain(f);
    removeTrain(c);
    printTrains();
    stuff();

    Message *msg1 = newMessage(10, 100);
    Message *msg2 = newMessage(20, 200);
    Message *msg3 = newMessage(30, 220);
    Message *msg4 = newMessage(40, 220);
    pushMessage(2, msg2);
    printMessageTree();
    pushMessage(1, msg1);
    printMessageTree();
    pushMessage(3, msg3);
    printMessageTree();
    pushMessage(4, msg4);
    printMessageTree();
    Message *msg = popMessage();
    printMessage(msg);
    printMessageTree();
    msg = popMessage();
    printMessage(msg);
    printMessageTree();
    msg = popMessage();
    printMessage(msg);
    printMessageTree();
    msg = popMessage();
    printMessage(msg);
    printMessageTree();

    msg = popMessage();
    if(msg == NULL){
        printf("No more messages!");
    }
    else{
        printf("msg val: %u\n", msg);
        printMessage(msg);
        printMessageTree();
    }

    //convertMessage(newMessage(2, 120));
    convertMessage(newMessage(30, 60));
    Byte ca = 30;
    Byte cb = 60;
    printf("%un", ca ^ cb);
}

