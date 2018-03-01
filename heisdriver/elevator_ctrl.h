#ifndef ELEVATOR_CTRL_H
#define ELEVATOR_CTRL_H

#include "elevator_io.h"
#include "timer.h"
#include "globals.h"
#include <stdio.h>

void printQueue();
void printState();

//initiates the elevator to go UP to the nearest floor (when program starts)
void elevatorInitiate();

//Opens/Closes the door and updates variable doorOpen
void openDoor();
void closeDoor();


//updates currentFloor if floor is reached
//sets floor indicator lamp of the currentFloor (or last known)
void updateFloorLight();

int getQueue(button_t button, int floor);

void addToQueue(button_t button, int floor);
void removeFromQueue(button_t button, int floor);

void checkButtonsAddToQueue();

void checkFloorReachedUpdateQueue();

void checkIfShouldStop();


//stops elevator when stop button is pressed
//deletes all orders in queue
//runs while button is pressed (so no orders can come in)
//
//if elevator is in floor when pressed: 
//  *the door is opened
//  *stays open three seconds after button is released
void handleEmergencyStop();



void update();



#endif