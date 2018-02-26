#include "illumination.h"

void setFloorLight(){
	if (getFloorSensor() != -1) {
         currentFloor = getFloorSensor();
    }

    elev_set_floor_indicator(currentFloor);
}