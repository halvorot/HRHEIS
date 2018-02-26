#ifndef ELEVATOR_CTRL_H
#define ELEVATOR_CTRL_H

#include "globals.h"

int getCurrentFloor();
void setCurrentFloor(int floor);

state_t getState();
void setState(state_t s);

direction_t getDirection();
void setDirection(direction_t dir);

int motorIsRunning();
int doorIsOpen();
int elevatorIsInFloor();

void elevatorInitiate();

void update();

#endif