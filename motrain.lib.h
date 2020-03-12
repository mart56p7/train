#include <stdbool.h>
//
// Created by abc on 07/03/2020.
//

#ifndef OPGAVER_MOTRAIN_LIB_H
#define OPGAVER_MOTRAIN_LIB_H

typedef unsigned char Train;
typedef unsigned char Byte;

struct TrainMessage// buffer for command
{
    // number of possible
    Byte data[7];
    // number of positions in use
    Byte len;
} typedef Message;

struct TransmissionMessage{
    Message *msg;
    Byte preamble; //Goes from starting value to 0
    Byte bytenum; //Return the msg data byte we are on
    Byte bytepos; //returns the position of the msg data byte we are on
    bool transmitting; //Returns if the current bit is still transmitting, default behaviour is high, then low.
    bool completed; //returns true is the transmissin is done, else false
    Byte transmissiontime; //set transmission length
} typedef TMessage;

struct TrainMessageNode{
    //The priority should have a value higher than 0 for anything else than emergency breaks. In general we suggest a default value of 5.
    Byte priority;
    //Internal prio is used internally to evaluate which command to execute, if multiple commands have the same priority.
    Message *message;
    struct TrainMessageNode *left;
    struct TrainMessageNode *right;
} typedef MessageNode;


void addTrain(Train train);
void removeTrain(Train train);
void printTrains();

Message* newMessage(Train train, Byte speed);
TMessage* newTMessage(Message *msg);
void pushMessage(Byte priority, Message *msg);
Message* popMessage();
MessageNode* getMessageQueue();
void printMessageTree();
void printMessage(Message *msg);



void sendBit(Byte bitval);
bool getBitNum(Byte bitval, Byte bitnum);
void sendByte(Byte byteval);

#endif //OPGAVER_MOTRAIN_LIB_H
