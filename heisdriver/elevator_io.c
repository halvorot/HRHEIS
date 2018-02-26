#include "elevator_io.h"


void startMotor() {
    elev_set_motor_direction(direction);
}

void stopMotor() {
    elev_set_motor_direction(DIRN_STOP);
}

void openDoor(){
    elev_set_door_open_lamp(1);
}

void closeDoor(){
    elev_set_door_open_lamp(0);
}

int getFloorSensor(){
    return elev_get_floor_sensor_signal();
}