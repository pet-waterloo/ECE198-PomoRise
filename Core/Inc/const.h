/*
 * const.h
 *
 *  Created on: Nov 16, 2023
 *      Author: petthepotat
 */

#ifndef INC_CONST_H_
#define INC_CONST_H_



const uint
	A_LEFT = 0,
	A_CENTER = 1,
	A_RIGHT = 2;


uint C_START_TIME = 0;
uint CURRENT_TIME = 0;
uint PREV_TIME = 0;
uint DELTA_TIME = 0;


const uint CLOCK_SIZE = 6;


// max duraciton is 15 s
const int ALARM_MAX_LENGTH = 15;

int CLOCK[6] = {0, 0, 0, 0, 0, 0};


#endif /* INC_CONST_H_ */
