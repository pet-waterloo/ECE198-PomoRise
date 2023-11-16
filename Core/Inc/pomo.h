/*
 * pomo.h
 *
 *  Created on: Nov 16, 2023
 *      Author: petthepotat
 */

#ifndef INC_POMO_H_
#define INC_POMO_H_


int D_MONTHS[] = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};


int C_START_TIME = 0;
int CURRENT_TIME = 0;
int PREV_TIME = 0;
int DELTA_TIME = 0;


const int CLOCK_SIZE = 6;

// -----

void second_update_clock(int* clock){
	// if ms > 1000ms  / 1 s
	if(DELTA_TIME < 1000) return;
	DELTA_TIME -= 1000;
	clock[0] ++;
	// end
	if(clock[0] >= 60){
		clock[0] = 0;
		clock[1] ++;
	}
	if(clock[1] >= 60){
		clock[1] = 0;
		clock[2]++;
	}
	if(clock[2] >= 24){
		clock[2] = 0;
		clock[3]++;
	}
	//c check if feb / leap year and is feb
	if(clock[5]% 4 == 0 && clock[4]== 2){
		if(clock[3] >= 29){
			clock[3] = 1;
			clock[4]++;
		}
	}else{
		// if not a leap year - do a normal check
		if(clock[3] >= D_MONTHS[clock[4]]){
			clock[3] = 1;
			clock[4]++;
		}
	}
	if(clock[4] >= 12){
		clock[4]= 1;
		clock[5]++;
	}
}






#endif /* INC_POMO_H_ */
