#ifndef ELEVATOR_CTRL_H
#define ELEVATOR_CTRL_H

#include "elevator_io.h"
#include "globals.h"



void elevatorInitiate();

void updateFloorLight();

void addToQueue(int floor, button_t button);
void removeFromQueue(int floor, button_t button);

void update();



#endif