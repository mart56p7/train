//
// Created by Oliver on 31-03-2020.
//
#include <stdbool.h>

#ifndef SIMULATOR_OBSERVER_H
#define SIMULATOR_OBSERVER_H

struct _train{
    int name;
    void (*function)();
} typedef Train;

struct _gauge{
    int name;
    void (*function)();
} typedef Gauge;

typedef unsigned char Byte;

void addTrain(Train train);
void removeTrain(Train train);
Train* getTrains();

void addGauge(Gauge gauge);
void removeGauge(Gauge gauge);
Gauge* getGauges();

void simulatorUpdate();
bool isCollision();





struct Rail{
    int length;
    //Next
    //Prev
}  typedef Rail;




#endif //SIMULATOR_OBSERVER_H
