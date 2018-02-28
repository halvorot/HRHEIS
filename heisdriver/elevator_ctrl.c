#include "elevator_ctrl.h"

state_t state;
direction_t direction;
int currentFloor;
int motorRunning;
int doorOpen;

int queue[N_FLOORS][3];



void elevatorInitiate(){
    direction = DIRN_UP;
    int floor = getFloorSensor();
    if(floor != -1){
        currentFloor = floor;
    }
    else{
        startMotor(direction);
        state = MOVING_UP;
        while(getFloorSensor() == -1){ /*intentionally empty, waits until it reaches floor*/ }
        stopMotor();
        direction = DIRN_STOP;
        state = WAIT;
    }
}

void updateFloorLight(){
	if (getFloorSensor() != -1) {
         currentFloor = getFloorSensor();
    }

    setFloorIndicator(currentFloor);
}

void addToQueue(int floor, button_t button){
    queue[floor][button] = 1;
}

void removeFromQueue(int floor, button_t button){
    queue[floor][button] = 0;
}


//removes the correct buttons from queue if the elevator reaches the floor (depending on direction)
void checkFloorReachedUpdateQueue(){
    for (int floor = 0; floor < N_FLOORS; ++i)
    {
        if(floor == getFloorSensor()){
            removeFromQueue(floor, BUTTON_COMMAND);
            if (direction == DIRN_UP)
                removeFromQueue(floor, BUTTON_CALL_UP);
            else if(direction == DIRN_DOWN)
                removeFromQueue(floor,BUTTON_CALL_DOWN);
        }
    }
}

//IKKE FERDIG/////////////////
void Queue(){
    if(direction == DIRN_UP){
        for (int i = currentFloor; i < N_FLOORS; ++i)
        {
            
        }
    }
    else if (direction == DIRN_DOWN){
        for (int i = 0; i < count; ++i)
        {
            /* code */
        }
    }
    else{

    }
}
////////////////////////

void update() {
    switch (state) {
        case MOVING_UP:
            direction = DIRN_UP;
            startMotor(direction);
            break;
        case MOVING_DOWN:
            direction = DIRN_DOWN;
            startMotor(direction);
            break;
        case WAIT:
            stopMotor();
            break;
        case EMERGENCY_STOP: //not in use yet
            break;
    }

    updateFloorLight();
    updateQueue();
}