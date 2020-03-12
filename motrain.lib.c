#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "motrain.lib.h"


/**
 * How it works!
 *
 * We are operating with 2 lists and 1 priority queue
 *
 * A train list, that contains the names of all trains
 * A send list, this is a list of 0 and 1 that are to be send
 * A Message priority queue (Binary Tree)
 *
 * We need to send idle messages every so often to keep the trains moving. Beside that we also needs to send commands if we want the trains to change state.
 *
 * The idle message is composed using the train list.
 *
 * Everytime our interrupt is fired, we make an active choice
 * are we done sending bits from the send queue?
 * NO? Send the next bit
 * Yes?
 * Is breaks set to anything higher than 0? If so we execute that amount of commands from the Message queue.
 * If breaks is 0, then we either do a command (if any are in the queue) or a nop command - all depending on messagequeuebusy, commandready, nopinterval, commandreset, commandincrement and commandvalue.
 *  if messagequeuebusy == 1 and the command is a message command, we do a nop command instead and increment commandready
 *  Everytime a NOP command is executed instead of a message commandready increment by 1, if a command from message queue is executed commandready resets to 0.
 *  if commandready is 1 or higher higher then the next message is executed immidiatly and commandready is reset to 0
 *
 *  To decide if we do a nop command or message,
 *  nopinterval >= commandvalue: do NOP
 *  else: do Message
 *  increment commandvalue by commandincrement and check if we need to reset it with commandreset
 * */

//************* GLOBAL VARIABLES: START **********************//

//Setting this variable to any value higher than 0, means that messages in the train message queue, are prioritised over doing NOP commands. Each time a message is completed, the breaks is lowered by 1.
Byte breaks = 0;
//This sets the break for when we start doing NOP commands, starting at the nopinterval number and continueing up to commandreset.
Byte nopinterval = 2;
//Sets when the commandnum is reset
Byte commandreset = 4;
//Internally used variable, increment each time a command is send by this amount
Byte commandincrement = 1;
//Internally used to store the current command value
Byte commandvalue = 0;
//increment everytime a nop command is run, if higher than commandreset execute command from command queue next.
Byte commandready = 0;

//Default max amount of trains are 5, defined in addTrain and maxtrains. The variables are to keep track of the train list
Byte curtrains = 0;
Byte maxtrains = 5;
Train *trains = NULL;

MessageNode *messagequeue = NULL;
//1 Indicates that a insert is in progress, then no element can be taken out of the msg queue.
//0 indicates that its safe to take messages out of the queue.
Byte messagequeuebusy = 0;

//************* GLOBAL VARIABLES: END **********************//

TMessage* newTMessage(Message *msg){
    TMessage *tmsg = malloc(sizeof(TMessage));
    tmsg->msg = msg;
    tmsg->preamble = 16;
    tmsg->bytenum = 0;
    tmsg->bytepos = 0;
    tmsg->transmitting = 0;
    tmsg->completed = 0;
}

void addTrain(Train train){
    //Check if train list has been initialized
    if(trains == NULL){
        trains = malloc(sizeof(Train) * 5);
    }
    //Remove the train from the list, this means that the train can only be found 1 time in the list!
    removeTrain(train);
    //Check if we need to resize
    if(maxtrains == curtrains){
        //Resize time
        if(curtrains > 123){
            maxtrains = 255;
        }
        else{
            maxtrains = 2 * curtrains;
        }
        Train *trains2 = (Train*) malloc(sizeof(Train) * maxtrains);
        trains2 = memcpy(trains2, trains, sizeof(Train) * curtrains);
        free(trains);
        trains = trains2;
        //numtrain()
    }
    *(trains+curtrains) = train;
    curtrains++;
}

void removeTrain(Train train){
    if(trains != NULL){
        for(int i = 0; i < curtrains; i++){
            if(*(trains+i) == train){
                //Makes sure that there are more elements in the array, before end of array
                if(i+1 != curtrains){
                    memcpy((trains+i), (trains+i+1), sizeof(Train) * (curtrains+1));
                }
                curtrains--;

            }
        }
    }
}

void printTrains(){
    printf("\n------ Trains print start ------\n");
    for(int i = 0; i < curtrains; i++){
        printf("Train %i: %u\n", i, *(trains+i));
    }
    printf("------ Trains print end ------\n");
}


Message* newMessage(Train train, Byte speed){
    Message *msg = malloc(sizeof(Message));
    msg->len = 3;
    msg->data[0] = train;
    msg->data[1] = speed;
    msg->data[2] = train ^ speed;
    msg->data[3] = 0;
    msg->data[4] = 0;
    msg->data[5] = 0;
    msg->data[6] = 0;
}

MessageNode* _newMessageNode(Byte priority, Message *msg){
    MessageNode *msgnode = malloc(sizeof(MessageNode));
    msgnode->priority = priority;
    msgnode->left = NULL;
    msgnode->right = NULL;
    msgnode->message = msg;
}

void _pushMessageNode(MessageNode *tree, MessageNode *node){
    //If the values are equal, we switch the tree node and the new node, this is done, so we dont have old "values" hang in the tree
    if(node->priority == tree->priority){
        node->left = tree->left;
        node->right = tree->right;
        tree->left = NULL;
        tree->right = NULL;
        MessageNode *cnode = node;
        node = tree;
        tree = cnode;
    }
    if(node->priority >= tree->priority){
        if(tree->right == NULL){
            tree->right = node;
            if(node->right == NULL){
            }
        }
        else{
            _pushMessageNode(tree->right, node);
        }
    }
    else{
        if(tree->left == NULL){
            tree->left = node;
        }
        else{
            _pushMessageNode(tree->left, node);
        }
    }
}

void pushMessage(Byte priority, Message *msg){
    printf("pushMessage\n");
    messagequeuebusy=1;
    MessageNode *node = _newMessageNode(priority, msg);
    if(messagequeue == NULL){
        messagequeue = node;
    }
    else{
        _pushMessageNode(messagequeue, node);
    }
    messagequeuebusy=0;
}

MessageNode* _popMessage(MessageNode *parent, MessageNode *tree){
    if(tree == NULL){
        return NULL;
    }

    if(tree->left != NULL){
        _popMessage(tree, tree->left);
    }
    else{
        if(parent == NULL){
            messagequeue = tree->right;
        }
        else{
            parent->left = NULL;
        }
        return tree;
    }
}

//we always return smallest value (most left leaf)
Message* popMessage(){
    messagequeuebusy=1;
    MessageNode *node = _popMessage(NULL, messagequeue);
    if(node == NULL){
        return NULL;
    }
    Message *msg = node->message;
    //Free MessageNode space allocated
    free(node);
    messagequeuebusy=0;
    return msg;
}

void _printMessageNode(MessageNode *tree){
    if(tree == NULL){
        return;
    }

    printf("Train: %u Priority: %u", tree->message->data[0], tree->priority);
    printf("{");
    _printMessageNode(tree->left);
    printf(",");
    _printMessageNode(tree->right);
    printf("}");

}

MessageNode* getMessageQueue(){
    return messagequeue;
}

void printMessageTree(){
    _printMessageNode(messagequeue);
    printf("\n");
}



void printMessage(Message* msg){
    printf("Msg data: %u %u %u %u %u %u %u Len: %u\n", msg->data[0], msg->data[1], msg->data[2], msg->data[3], msg->data[4], msg->data[5], msg->data[6], msg->len);
}

void sendBit(Byte bitval){
    if((bitval & (1 << 0)) > 0){
        //Send 1
        printf("1\n");
    }
    else{
        //Send 0
        printf("0\n");
    }
}

bool getBitNum(Byte bitval, Byte bitnum){
    return (bitval & (1 << bitnum)) > 0;
}

void sendByte(Byte byteval){
    for(int i = 7; i >= 0; i--){
        if((byteval & (1 << i)) > 0){
            //Send 1
            printf("1\n");
        }
        else{
            //Send 0
            printf("0\n");
        }
    }
}