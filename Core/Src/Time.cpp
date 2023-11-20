/*
 * Time.cpp
 *
 *  Created on: Nov 20, 2023
 *      Author: petthepotat
 */


#include <Time.hpp>

Time::Time(int ss, int mm, int hh, int DD, int MM, int YY) :
		sec(ss), min(mm), hrr(hh), day(DD), mth(MM), yrr(YY) {
	// TODO Auto-generated constructor stub
	START_TIME = HAL_GetTick();
	DELTA_TIME = 0;
	END_TIME = 0;
}

Time::~Time() {
	// TODO Auto-generated destructor stub
}


uint Time::get_sec(){
	return this->sec;
}

uint Time::get_min(){
	return this->min;
}
uint Time::get_hrr(){
	return this->hrr;
}
uint Time::get_day(){
	return this->day;
}
uint Time::get_mth(){
	return this->mth;
}
uint Time::get_yrr(){
	return this->yrr;
}

void Time::update_time(){
	END_TIME = HAL_GetTick();
	DELTA_TIME += END_TIME - START_TIME;
	START_TIME = END_TIME;

	// checks
	if(DELTA_TIME < 1000) return;
	DELTA_TIME -= 1000;
	this->sec++;

	// check time changes
	if(this->sec < 60) return;
	this->min++;
	this->sec = 0;

	if(this->min < 60) return;
	this->hrr ++;
	this->min = 0;

	if(this->hrr < 24) return;
	this->day ++;
	this->hrr = 0;

	// check for leap year
	if(this->mth != FEB){
		if(this->day < D_MONTHS[this->mth]) return;
	}else{
		if(this->yrr % 4 != 0) return;
		// if it is a leap year and its a feb
		if(this->day < 28) return;
	}
	// all condintinos passed
	this->mth ++;
	this->day = 1;

	if(this->mth < 12) return;
	this->yrr++;
	this->mth = JAN;
}

void Time::to_string(char* buf){
	char a[3], b[3];
	min_2_dig(a, this->hrr);
	min_2_dig(b, this->min);
	sprintf(buf, "%s %-2i     %s:%s", M_STRING[this->mth], this->day,
				a, b);
}

void Time::set_time(int ss, int mm, int hh, int DD, int MM, int YY){
	this->sec = ss;
	this->min = mm;
	this->hrr = hh;
	this->day = DD;
	this->mth = MM;
	this->yrr = YY;
}

void min_2_dig(char* buf, int num){
	if(num > 9) sprintf(buf, "0%i", num);
	else sprintf(buf, "%i", num);
}




