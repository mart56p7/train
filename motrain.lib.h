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
void pushMessage(Byte priority, Message *msg);
Message* popMessage();
MessageNode* getMessageQueue();
void printMessageTree();
void printMessage(Message *msg);

Byte* convertMessage(Message *msg);
//Something with Command getCommand();

void sendBit(Byte bitval);
void sendByte(Byte byteval);

#endif //OPGAVER_MOTRAIN_LIB_H
