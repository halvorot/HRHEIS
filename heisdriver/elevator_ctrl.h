#ifndef ELEVATOR_CTRL_H
#define ELEVATOR_CTRL_H

#include "elevator_io.h"
#include "timer.h"
#include "globals.h"
#include <stdio.h>


//Functions for debugging and check what happens
void printQueue();
void printState();

//initiates the elevator to go UP to the nearest floor (when program starts)
//sets state to WAIT when floor is reached
void elevatorInitiate();

//Opens/Closes the door and updates variable doorOpen
void openDoor();
void closeDoor();


//updates currentFloor if floor is reached
//sets floor indicator lamp of the currentFloor (or last known)
void updateFloorLight();

int getQueue(button_t button, int floor);


//adds or removes an order from the queue
void addToQueue(button_t button, int floor);
void removeFromQueue(button_t button, int floor);

//Checks if any of the ordering buttons are pressed and adds the order to queue if they are
void checkButtonsAddToQueue();

//removes the correct btns from queue and turns off btn light if the elevator reaches the floor and door opens
void checkFloorReachedUpdateQueue();


//checks if the elevator should stop
//Stops if the floor is ordered by COMMAND button
void checkIfShouldStop();



//stops elevator when stop button is pressed
//deletes all orders in queue
//runs while button is pressed (so no orders can come in)
//
//if elevator is in floor when pressed: 
//  *the door is opened
//  *stays open three seconds after button is released
void handleEmergencyStop();




//HAS MAIN FUNCTIONALITY
//checks if buttons are pressed
//checks if a floor is reached and removes it from the queue
//chechs if elevator should stop at floor
//updates the floor light
//Tells elevator what to do depending on which STATE it is in
void update();



#endif