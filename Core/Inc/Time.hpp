/*
 * Time.h
 *
 *  Created on: Nov 20, 2023
 *      Author: petthepotat
 */

#ifndef INC_TIME_HPP_
#define INC_TIME_HPP_

#define uint unsigned int

#include <string>
#include <stdio.h>

#include "tim.h"
#include "gpio.h"
#include "main.h"



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


uint D_MONTHS[] = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

char *M_STRING[] = {
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

// -------



class Time {
private:
	uint START_TIME;
	uint DELTA_TIME;
	uint END_TIME;


	uint sec;
	uint min;
	uint hrr;
	uint day;
	uint mth;
	uint yrr;
public:
	Time(int ss, int mm, int hh, int DD, int MM, int YY);
	virtual ~Time();


	uint get_sec();
	uint get_min();
	uint get_hrr();
	uint get_day();
	uint get_mth();
	uint get_yrr();

	// use size 16 buff
	void to_string(char*);
	void update_time();
	void set_time(int ss, int mm, int hh, int DD, int MM, int YY);

};

// use size 3 bufs
void min_2_dig(char* buf, int num);

#endif /* INC_TIME_HPP_ */
