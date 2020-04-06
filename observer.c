//
// Created by Oliver on 31-03-2020.
//

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "observer.h"

Byte curtrains = 0;
Byte maxtrains = 5;
Train *trains = NULL;

Byte curgauges = 0;
Byte maxgauges = 5;
Gauge *gauges = NULL;


// TRAINS
void addTrain(Train train){
    //Check if train list has been initialized
    if(trains == NULL){
        trains = malloc(sizeof(Train) * maxtrains);
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
    }
    *(trains+curtrains) = train;
    curtrains++;
}

void removeTrain(Train train){
    if(trains != NULL){
        for(int i = 0; i < curtrains; i++){
            if((trains+i)->name == train.name){
                //Makes sure that there are more elements in the array, before end of array
                if(i+1 != curtrains){
                    memcpy((trains+i), (trains+i+1), sizeof(Train) * (curtrains+1));
                }
                curtrains--;
            }
        }
    }
}

Train* getTrains(){
    return trains;
}




// Gauges
void addGauge(Gauge gauge){
    //Check if gauge list has been initialized
    if(gauges == NULL){
        gauges = malloc(sizeof(Gauge) * maxgauges);
    }
    //Remove the gauge from the list, this means that the gauge can only be found 1 time in the list!
    removeGauge(gauge);
    //Check if we need to resize
    if(maxgauges == curgauges){
        //Resize time
        if(curgauges > 123){
            maxgauges = 255;
        }
        else{
            maxgauges = 2 * curgauges;
        }
        Gauge *gauges2 = (Gauge*) malloc(sizeof(Gauge) * maxgauges);
        gauges2 = memcpy(gauges2, gauges, sizeof(Gauge) * curgauges);
        free(gauges);
        gauges = gauges2;
    }
    *(gauges+curgauges) = gauge;
    curgauges++;
}

void removeGauge(Gauge gauge){
    if(gauges != NULL){
        for(int i = 0; i < curgauges; i++){
            if((gauges+i)->name == gauge.name){
                //Makes sure that there are more elements in the array, before end of array
                if(i+1 != curgauges){
                    memcpy((gauges+i), (gauges+i+1), sizeof(Gauge) * (curgauges+1));
                }
                curgauges--;
            }
        }
    }
}

Gauge* getGauges(){
    return gauges;
}




// LOGIC
void simulatorUpdate(){
    for (int i = 0; i < curtrains; ++i) {
        Train t = *(trains+i);
        t.function();
    }

    for (int i = 0; i < curgauges; ++i) {
        Gauge g = *(gauges+i);
        g.function();
    }
}

bool isCollision(){
    return false;   // Fix later
}
