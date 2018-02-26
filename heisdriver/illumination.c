#include "illumination.h"

void setFloorLight(){
	if (getFloorSensor() != -1) {
         setCurrentFloor(getFloorSensor());
    }

    elev_set_floor_indicator(getCurrentFloor());
}