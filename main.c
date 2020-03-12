#include <stdio.h>
#include <stdlib.h>
#include "motrain.lib.h"

void stuff(){
    printTrains();
}

void send(TMessage *tmsg){
    if(tmsg->transmitting){
        //Set transmissiontime
        //set voltage low
        tmsg->transmitting = 0;
        return;
    }
    if(tmsg->preamble > 0){
        sendBit(1);
        tmsg->preamble--;
    }
    else{
        if(tmsg->msg != NULL && tmsg->bytenum < tmsg->msg->len){
            if(tmsg->bytepos == 8){
                if(tmsg->bytenum+1 == tmsg->msg->len){
                    //Set transmissiontime
                    //set voltage high
                    sendBit(1);
                }
                else{
                    //Set transmissiontime
                    //set voltage low
                    sendBit(0);
                }
                tmsg->bytepos = 0;
                tmsg->bytenum++;
            }else{
                sendBit(getBitNum(tmsg->msg->data[tmsg->bytenum], tmsg->bytepos));
                //Set transmissiontime
                //set voltage low or high
                tmsg->bytepos++;
            }
        }
        else{
            if(tmsg->completed == 0){
                tmsg->completed = 1;
            }
        }
    }
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
    /*
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
    }*/

    while(getMessageQueue() > 0){
        Message *msg = popMessage();
        printMessage(msg);
        printMessageTree();
        TMessage* nmsg = newTMessage(msg);
        while(nmsg->completed == 0){
            send(nmsg);
        }
    }
    //convertMessage(newMessage(2, 120));
    //convertMessage(newMessage(30, 60));
    /*
    Byte* bitlist = NULL;
    int* bitlistsize = malloc(sizeof(int));
    int* bitlistpos = malloc(sizeof(int));
    *bitlistpos = 0;
    */


}

