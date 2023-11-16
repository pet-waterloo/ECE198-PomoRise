/*
 * timer.h
 *
 *  Created on: Nov 16, 2023
 *      Author: petthepotat
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_


int ALARM[] = {0, 0, 0, 0, 0, 0};


// ---
void set_alarm(int *data){
	for (int i = 0; i < CLOCK_SIZE; i++){
		ALARM[i] = data[i];
	}
	// clear data
	delete data;
	data = nullptr;
}

void delete_alarm(){
	for (int i = 0; i < CLOCK_SIZE; i++){
		ALARM[i] = 0;
	}
}






#endif /* INC_TIMER_H_ */
