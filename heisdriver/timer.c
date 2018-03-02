#include "timer.h"

int timerActive=0;
clock_t startClock;//LITT USIKKER PÅ CLOCK_T
clock_t currentClock;


void startTimer(){
	timerActive=1;
	startClock=clock();
	currentClock=clock();
}


int timerTimeOut(){
	if(timerActive){
		currentClock=clock();
	}
	printf("Timer: %ld \n", (currentClock-startClock)/CLOCKS_PER_SEC );
	if(((currentClock-startClock)/CLOCKS_PER_SEC) >= 3){
		stopTimer();
		return 1;
	}
	return 0;
}

void stopTimer(){
	timerActive=0;
}