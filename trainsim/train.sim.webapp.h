//
// Created by abc on 31/03/2020.
//

#ifndef TRAINSIM_TRAIN_SIM_WEBAPP_H
#define TRAINSIM_TRAIN_SIM_WEBAPP_H
int restServerStart(int port);
int staticServerStart(int port);

struct StringMessage{
    char* msg;
    int length;
};

typedef struct  StringMessage strmsg;

#endif //TRAINSIM_TRAIN_SIM_WEBAPP_H
