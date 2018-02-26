#ifndef ELEVATOR_IO_H
#define ELEVATOR_IO_H

#include "globals.h"

void startMotor();
void stopMotor();

void openDoor();
void closeDoor();

int getFloorSensor();

int getButton(button_t button, int floor);

#endif