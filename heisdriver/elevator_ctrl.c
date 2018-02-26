#include "globals.h"

direction_t direction = DIRN_UP;
int currentFloor = -1;
state_t state = MOVING_UP;
int motorRunning = 1;
int doorOpen = 0;



int getCurrentFloor() {
    return currentFloor;
}
void setCurrentFloor(int floor){
    currentFloor = floor;
}

state_t getState() {
    return state;
}

void setState(state_t s){
    state = s;
    switch (state) {
        case MOVING_UP:
            direction = DIRN_UP;
            startMotor();
            break;
        case MOVING_DOWN:
            direction = DIRN_DOWN;
            startMotor();
            break;
        case WAIT:
            direction = DIRN_STOP;
            stopMotor();
            break;
        case EMERGENCY_STOP: //not in use yet
            break;
    }
}

direction_t getDirection() {
    return direction;
}
void setDirection(direction_t dir){
    direction = dir;
}

int motorIsRunning(){
    return motorRunning;
}

int doorIsOpen(){
    return doorOpen;
}



void elevatorInitiate(){
    int floor = getFloorSensor();
    if(floor != -1){
        setCurrentFloor(floor);
    }
    else{
        setState(MOVING_UP);
        while(getFloorSensor() == -1){ /*intentionally empty, waits until it reaches floor*/ }
        setState(WAIT);
    }
}

void update() {
    setFloorLight();
}