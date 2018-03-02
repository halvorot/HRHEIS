#ifndef ELEVATOR_CTRL_H
#define ELEVATOR_CTRL_H

#include "elevator_io.h"
#include "timer.h"
#include "globals.h"
#include <stdio.h>



//initiates the elevator to go UP to the nearest floor (when program starts)
//sets state to WAIT when floor is reached
void elevatorInitiate();


void changeState(state_t s);


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

//checks queue above the elevator
int checkUpwards();

//checks queue beneath the elevator
int checkDownwards();

//checks all directions, all floor buttons
void checkAllButtons();

//Checks if any of the ordering buttons are pressed and adds the order to queue if they are
void checkButtonsAddToQueue();

//removes the correct btns from queue and turns off btn light if the elevator reaches the floor and door opens
void checkFloorReachedUpdateQueue();


//checks if the elevator should stop
//Stops if the floor is ordered by COMMAND button
void checkIfShouldStop();



//handles what happens when stop button is pressed
void handleEmergencyStop();




//HAS MAIN FUNCTIONALITY
//checks if buttons are pressed
//checks if a floor is reached and removes it from the queue
//chechs if elevator should stop at floor
//updates the floor light
//Tells elevator what to do depending on which STATE it is in
void update();



#endif