#include "elevator_io.h"

void startMotor() {
    if (getFloorSensor() != TOP_FLOOR || getDirection() == DOWN) {
        elev_set_motor_direction(getDirection());
    }
    if (getFloorSensor() != BOTTOM_FLOOR || getDirection() == UP) {
        elev_set_motor_direction(getDirection());
    }
}

void stopMotor() {
    elev_set_motor_direction(STOP);
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