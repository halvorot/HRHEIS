#ifndef ELEVATOR_CTRL_H
#define ELEVATOR_CTRL_H

#include "elevator_io.h"
#include "globals.h"



state_t getState();

void setState(state_t s);

void elevatorInitiate();

void setFloorLight();

void update();



#endif