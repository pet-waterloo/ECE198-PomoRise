/*
 * timer.h
 *
 *  Created on: Nov 16, 2023
 *      Author: petthepotat
 */

#pragma once

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "const.h"
#include "pomo.h"
#include "speaker.h"
#include "stdbool.h"


int ALARM[] = {0, 0, 0, 0, 0, 0};
int SPEAKER_ACTIVE_TIMER[] = {0, 0, 0, 0, 0, 0};
bool HAS_TIMER = false;

int POMO_TIMER[] = {0, 0, 0, 0, 0, 0};
bool IS_POMO = false;


// ---
void set_alarm_arr(int*);
void set_alarm(int, int, int);
void delete_alarm();
void update_speaker_limit();
void update_alarm();


void set_alarm_arr(int *data){
	HAS_TIMER = true;
	int a = data[0], b = data[1], c = data[2];
	set_alarm(a, b, c);
}

void set_alarm(int ss, int mm, int hh){
	HAS_TIMER = true;
	ALARM[SEC] = ss;
	ALARM[MIN] = mm;
	ALARM[HRR] = hh;
	// set the rest to be next day and current year / month
	// if next day is greater than month limit, and if next month is greater than year limit
	// move to next year, first day
	if(CLOCK[DAY] + 1 > D_MONTHS[CLOCK[MON]]){
		// check if new year
		if(CLOCK[MON] + 1 > 12){
			ALARM[YRR] = CLOCK[YRR] + 1;
			ALARM[MON] = JAN;
			ALARM[DAY] = 1;
		}else{
			ALARM[YRR] = CLOCK[YRR];
			ALARM[MON] = CLOCK[MON] + 1;
			ALARM[DAY] = 1;
		}
	} else {
		// if NOT illegal, just move to next day
		ALARM[YRR] = CLOCK[YRR];
		ALARM[MON] = CLOCK[MON];
		ALARM[DAY] = CLOCK[DAY] + 1;
	}
}

void delete_alarm(){
	HAS_TIMER = false;
	delete_clock(ALARM);
}


void update_alarm(){
	if(!HAS_TIMER) return;
	// check if alarm time is passed
	if(t1_passed_t2(CLOCK, ALARM)){
		// alarm go off
		set_speaker_state(true);
	}
}

void update_speaker_limit(){
	// limits all speaker time lengths to 15s
	if(SPEAKER_ACTIVE){
		SPEAKER_ACTIVE_TIMER[SEC] = CURRENT_TIME - SPEAKER_ACTIVE_START_TIME;
		// TODO REMOTE THIS NEXT LINE
		SPEAKER_ACTIVE_TIMER[MIN] = SPEAKER_ACTIVE_TIMER[SEC];
		if(SPEAKER_ACTIVE_TIMER[SEC] > ALARM_MAX_LENGTH){
			set_speaker_state(false);
			delete_clock(SPEAKER_ACTIVE_TIMER);
		}
	}
}

// ---
void start_pomo(int*);
void end_pomo();


void start_pomo(int* pc){
	IS_POMO = true;
	for(int i = 0; i < CLOCK_SIZE; i++){
		POMO_TIMER[i] = pc[i];
	}
}

void end_pomo(){
	IS_POMO = false;
	// activate speaker
	set_speaker_state(true);
}


#endif /* INC_TIMER_H_ */
