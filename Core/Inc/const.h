/*
 * const.h
 *
 *  Created on: Nov 16, 2023
 *      Author: petthepotat
 */

#ifndef INC_CONST_H_
#define INC_CONST_H_



// constnats for months
const uint
	JAN = 0,
	FEB = 1,
	MAR = 2,
	APR = 3,
	MAY = 4,
	JUN = 5,
	JUL = 6,
	AUG = 7,
	SEP = 8,
	OCT = 9,
	NOV = 10,
	DEC = 11;

// constants for clock
const uint
	SEC = 0,
	MIN = 1,
	HRR = 2,
	DAY = 3,
	MON = 4,
	YRR = 5;

uint D_MONTHS[] = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

const char *M_STRING[] = {
	"JAN",
	"FEB",
	"MAR",
	"APR",
	"MAY",
	"JUN",
	"JUL",
	"AUG",
	"SEP",
	"OCT",
	"NOV",
	"DEC"
};

const uint
	A_LEFT = 0,
	A_CENTER = 1,
	A_RIGHT = 2;


uint C_START_TIME = 0;
uint CURRENT_TIME = 0;
uint PREV_TIME = 0;
uint DELTA_TIME = 0;
uint TEMP_DELTA_TIME = 0;


const uint CLOCK_SIZE = 6;


// max duraciton is 15 s
const int ALARM_MAX_LENGTH = 15;

int CLOCK[6] = {0, 0, 0, 0, 0, 0};


#endif /* INC_CONST_H_ */
