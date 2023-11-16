/*
 * speaker.h
 *
 *  Created on: Nov 16, 2023
 *      Author: petthepotat
 */

#ifndef INC_SPEAKER_H_
#define INC_SPEAKER_H_

#include "stdbool.h"


bool SPEAKER_ACTIVE = false;
int SPEAKER_HERTZ = 500;
int SPEAKER_ACTIVE_START_TIME = 0;


// ---
void set_speaker_state(bool);


void set_speaker_state(bool state){
	SPEAKER_ACTIVE = state;
	SPEAKER_ACTIVE_START_TIME = CURRENT_TIME;
	// check if active
	if(state){
		htim2.Instance->CCR1 = SPEAKER_HERTZ;
	}else{
		htim2.Instance->CCR1 = 0;
	}
}






#endif /* INC_SPEAKER_H_ */
