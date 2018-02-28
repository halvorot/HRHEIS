#ifndef ELEVATOR_IO_H
#define ELEVATOR_IO_H

#include "elev.h"
#include "globals.h"

void startMotor(drection_t dir);
void stopMotor();

void openDoor();
void closeDoor();

int getFloorSensor();

int getButton(button_t button, int floor);

int stopIsPressed();

void setStopLamp();
void resetStopLamp();

void setFloorIndicator(int currFloor);

#endif