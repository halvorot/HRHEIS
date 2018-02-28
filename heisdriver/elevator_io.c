#include "elevator_io.h"
//test git

void startMotor(direction_t dir) {
    elev_set_motor_direction(dir);
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

int stopIsPressed(){
	return elev_get_stop_signal();
}

void setStopLamp(){
	elev_set_stop_lamp(1);
}
void resetStopLamp(){
	elev_set_stop_lamp(0);
}

void setFloorIndicator(int currFloor){
	elev_set_floor_indicator(currFloor);
}