#include "elevator_ctrl.h"

state_t state; //MOVING_UP, MOVING_DOWN or WAIT (OR EMERGENCY_STOP)
direction_t direction; //keeps track of what direction we are (or last were) moving in
int currentFloor; //keeps track of what floor we are (or last were) in.
int doorOpen;

int queue[N_FLOORS][3];

void printQueue(){
    for(int i = 0; i< N_FLOORS;i++){
        for(int j = 0; j< 3;j++){
            printf("%d ", queue[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void printState(){
    if(state == MOVING_UP)
        printf("state = MOVING_UP");
    else if(state == MOVING_DOWN)
        printf("state = MOVING_DOWN");
    else if(state == WAIT)
        printf("state = WAIT");
    
    printf("\n%d \n", direction);
}

void elevatorInitiate(){
    direction = DIRN_UP;
    int floor = getFloorSensor();
    if(floor != -1){//if elevator is in floor
        currentFloor = floor;
        state = WAIT;
    }
    else{
        startMotor(direction);
        state = MOVING_UP;
        while(getFloorSensor() == -1){ /*intentionally empty, waits until it reaches floor*/ }
        stopMotor();
        state = WAIT;
    }
}


void openDoor(){
    setDoorLight();
    doorOpen = 1;
}
void closeDoor(){
    resetDoorLight();
    doorOpen = 0;
}



void updateFloorLight(){
	if (getFloorSensor() != -1) {
         currentFloor = getFloorSensor();
    }

    setFloorIndicator(currentFloor);
}

int getQueue(button_t button, int floor){
    return queue[floor][button];
}

void addToQueue(button_t button, int floor){
    queue[floor][button] = 1;
    setButtonLamp(button, floor);
}

void removeFromQueue(button_t button, int floor){
    queue[floor][button] = 0;
    resetButtonLamp(button, floor);
}


//removes the correct btns from queue and turns off btn light if the elevator reaches the floor and opens door 
//(depending on direction)
void checkFloorReachedUpdateQueue(){
    for (int floor = 0; floor < N_FLOORS; ++floor)
    {
        if(floor == getFloorSensor() && doorOpen){
            removeFromQueue(BUTTON_COMMAND, floor);
            if (direction == DIRN_UP && floor != TOP_FLOOR){
                removeFromQueue(BUTTON_CALL_UP, floor);
            }
            else if(direction == DIRN_DOWN && floor != BOTTOM_FLOOR){
                removeFromQueue(BUTTON_CALL_DOWN, floor);
            }
        }
    }
}


void checkButtonsAddToQueue(){
    for (int floor = 0; floor < N_FLOORS; ++floor)
    {
        if (floor != 0 && buttonPressed(BUTTON_CALL_DOWN, floor)){
            addToQueue(BUTTON_CALL_DOWN, floor);
        }
        if (floor != TOP_FLOOR && buttonPressed(BUTTON_CALL_UP, floor)){
            addToQueue(BUTTON_CALL_UP, floor);
        }
        if(buttonPressed(BUTTON_COMMAND, floor)){
            addToQueue(BUTTON_COMMAND, floor);
        }
    }
}

// HAR BARE LAGT INN CHECK FOR COMMAND BUTTONS
void checkIfShouldStop(){
    for(int floor = 0; floor < N_FLOORS; floor++){
        if(getQueue(BUTTON_COMMAND, floor) && getFloorSensor() == floor){
            state = WAIT;
        }
        //IKKE FERDIG, MÅ LEGGE INN FLERE SJEKKER FOR RETNING OSV.
        if(floor != TOP_FLOOR && getQueue(BUTTON_CALL_UP, floor) && getFloorSensor() == floor){
            state = WAIT;
        }
        if(floor != BOTTOM_FLOOR && getQueue(BUTTON_CALL_DOWN, floor) && getFloorSensor() == floor){
            state = WAIT;
        }
    }
}


///////////IKKE FERDIG///////////////////////
void handleEmergencyStop(){
    //stops elevator
    stopMotor();
    for (int i = 0; i < N_FLOORS; ++i) {//deletes all orders in queue
        if (i != 0)
            removeFromQueue(BUTTON_CALL_DOWN, i);

        if (i != N_FLOORS - 1)
            removeFromQueue(BUTTON_CALL_UP, i);

        removeFromQueue(BUTTON_COMMAND, i);
    }

    if(getFloorSensor() != -1){//if elevator is in floor when pressed: the door is opened, timer starts
        currentFloor = getFloorSensor();
        openDoor();
        startTimer();
    }

    while(stopIsPressed()){//runs while button is pressed (so no orders can come in)
        startTimer();

    }
}
/////////////////////////////////


void update() {
    /*if(stopIsPressed()){
        state = EMERGENCY_STOP;
    }*/
    printState();
    printQueue();

    checkButtonsAddToQueue();
    checkFloorReachedUpdateQueue();
    updateFloorLight();

    checkIfShouldStop();

    switch (state) {
        case MOVING_UP:
            closeDoor();
            direction = DIRN_UP;
            startMotor(direction);
            if(getFloorSensor() == TOP_FLOOR){
                printState();
                stopMotor();
                state = WAIT;
            }
            break;
        case MOVING_DOWN:
            closeDoor();
            direction = DIRN_DOWN;
            startMotor(direction);
            if(getFloorSensor() == BOTTOM_FLOOR){
                printState();
                stopMotor();
                state = WAIT;
            }
            break;
        case WAIT: //if elevator waiting in a floor
            openDoor();
            stopMotor();
            startTimer();
            //if(timerTimeOut()){ //Hvis timer > 3
                stopTimer();
                //closeDoor();
                int foundOrder = 0;
                if(direction == DIRN_UP){
                    for (int i = currentFloor+1; i < N_FLOORS; ++i){
                        if(getQueue(BUTTON_CALL_UP, i) || getQueue(BUTTON_COMMAND, i)){
                            state = MOVING_UP;
                            foundOrder = 1;
                        }
                    }
                    if(!foundOrder){
                        direction = DIRN_DOWN;
                    }
                }
                else if(direction == DIRN_DOWN){
                    for (int i = currentFloor-1; i >= BOTTOM_FLOOR; --i){
                        if (getQueue(BUTTON_CALL_DOWN, i) || getQueue(BUTTON_COMMAND, i)){
                            state = MOVING_DOWN;
                            foundOrder = 1;
                        }
                    }
                    if(!foundOrder){
                        direction = DIRN_UP;
                    }
                }
            //}
            break;
        case EMERGENCY_STOP:
            //handleEmergencyStop();
            break;
    }
}