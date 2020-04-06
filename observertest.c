#include <stdio.h>
#include "observer.h"


// Sørg for at hver Train / Gauge har et name (int) og en function (void).
// Navn skal være unikt, ellers vil den ikke blive godtaget.
// Brug addTrain(Train) / addGauge(Gauge) til at tilføje et Train / Gauge til subscribers.
// Brug SimulatorUpdate() til at aktivere function i hver Train / Gauge der er subscribed.
// Brug removeTrain(Train) / removeGauge(Gauge) til at fjerne et Train / Gauge fra subscribers.



// Test stuff

void trainTest(){
    printf("I am a Train!\n");
}

void gaugeTest(){
    printf("I am a Rail Gauge!\n");
}


int main() {
    printf("Hello, World!\n");
    Train t1;
    t1.name = 1;
    t1.function = &trainTest;
    addTrain(t1);
    Train t2;
    t2.name = 2;
    t2.function = &trainTest;
    addTrain(t2);
    Gauge g1;
    g1.name = 1;
    g1.function = &gaugeTest;
    addGauge(g1);
    simulatorUpdate();
    removeTrain(t1);
    removeTrain(t2);
    simulatorUpdate();
    return 0;
}




