#include "elevator_ctrl.h"

state_t state;
direction_t direction;
int currentFloor;
int motorRunning;
int doorOpen;


void elevatorInitiate(){
    direction = DIRN_UP;
    int floor = getFloorSensor();
    if(floor != -1){
        currentFloor = floor;
    }
    else{
        setState(MOVING_UP);
        while(getFloorSensor() == -1){ /*intentionally empty, waits until it reaches floor*/ }
        setState(WAIT);
    }
}

void setFloorLight(){
	if (getFloorSensor() != -1) {
         currentFloor = getFloorSensor();
    }

    elev_set_floor_indicator(currentFloor);
}

void update() {
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


    setFloorLight();
}