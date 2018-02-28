#include "timer.h"

int timerActive=0;
clock_t startClock;//LITT USIKKER PÅ CLOCK_T
clock_t currentClock;


void startTimer(){
	timerActive=1;
	startClock=clock();
}


int timerTimeOut(){
	if(timerActive){
		currentClock=clock();
		if(((currentClock-startClock)/CLOCKS_PER_SEC) > 3){
			stopTimer();
			return 1;
		}
	}
}

void stopTimer(){
	timerActive=0;
}