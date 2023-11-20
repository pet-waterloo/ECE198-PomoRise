/*
 * pomo.h
 *
 *  Created on: Nov 16, 2023
 *      Author: petthepotat
 */

#pragma once

#ifndef INC_POMO_H_
#define INC_POMO_H_

#ifndef uint
#define uint unsigned int
#endif

#include "const.h"
#include "stdbool.h"
#include "timer.h"




int DEFAULT_POMO_LENGTH = 20;
int POMO_CLOCK[6] = {0, 20, 0, 0 ,0, 0};
bool POMO_ALARM = false;

int POMO_ALARM_LENGTH = 0;


void pomo_countdown(int* timer){
	if(DELTA_TIME < 1000) return;

	DELTA_TIME -= 1000;
	timer[SEC] --;
	if(timer[SEC] < 1){
		if(timer[MIN] != 0){
			timer[SEC] = 60;
			timer[MIN] --;
		}else{
			// end the timer + everything
			POMO_ALARM = true;
		}
	}
}

// -----
void set_clock_time_arr(int*);
void set_clock_time(int, int, int, int, int, int);
void second_update_clock(int*);
void display_info_s(Lcd_HandleTypeDef*, uint, char*, uint, uint, char*, uint);
void display_info_i(Lcd_HandleTypeDef*, uint, int, uint, int);
void display_clock(Lcd_HandleTypeDef*, int*);
void display_pomo(Lcd_HandleTypeDef*, int*);
int t1_passed_t2(int*, int*);
int get_display_pos(uint, uint);
int get_int_length(int);
void delete_clock(int*);

// -----
void delete_clock(int* clock){
	for (int i = 0; i < CLOCK_SIZE; i++){
		ALARM[i] = 0;
	}
}

void set_clock_time_arr(int* time){
	for(int i = 0; i < CLOCK_SIZE; i++){
		CLOCK[i] = time[i];
	}
}

void set_clock_time(int ss, int mm, int hh, int DD, int MM, int YY){
	CLOCK[SEC] = ss;
	CLOCK[MIN] = mm;
	CLOCK[HRR] = hh;
	CLOCK[DAY] = DD;
	CLOCK[MON] = MM;
	CLOCK[YRR] = YY;
}

void second_update_clock(int* clock){
	// if ms > 1000ms  / 1 s
	if(DELTA_TIME < 1000) return;
	DELTA_TIME -= 1000;
	clock[SEC] ++;
	// end
	if(clock[SEC] >= 60){
		clock[SEC] = 0;
		clock[MIN] ++;
	}
	if(clock[MIN] >= 60){
		clock[MIN] = 0;
		clock[HRR]++;
	}
	if(clock[HRR] >= 24){
		clock[HRR] = 0;
		clock[DAY]++;
	}
	//c check if feb / leap year and is feb
	if(clock[YRR]% 4 == 0 && clock[MON]== 2){
		if(clock[DAY] >= 29){
			clock[DAY] = 1;
			clock[MON]++;
		}
	}else{
		// if not a leap year - do a normal check
		if(clock[DAY] >= D_MONTHS[clock[MON]]){
			clock[DAY] = 1;
			clock[MON]++;
		}
	}
	if(clock[MON] >= 12){
		clock[MON]= 1;
		clock[YRR]++;
	}
}

void display_info_s(Lcd_HandleTypeDef* lcd, uint align1, char* data1, uint length1, uint align2, char* data2, uint length2){
	// get cursor position for each row
	int left1 = get_display_pos(align1, length1);
	int left2 = get_display_pos(align2, length2);



	// set cursor to position and draw
	Lcd_cursor(lcd, 0, left1);
	Lcd_string(lcd, data1);
	Lcd_cursor(lcd, 1, left2);
	Lcd_string(lcd, data2);

	// end
}

void display_info_i(Lcd_HandleTypeDef* lcd, uint align1, int data1, uint align2, int data2){
	// get cursor position for each row
	int left1 = get_display_pos(align1, get_int_length(data1));
	int left2 = get_display_pos(align2, get_int_length(data2));

	// set cursor to position and draw
	Lcd_cursor(lcd, 0, left1);
	Lcd_int(lcd, data1);
	Lcd_cursor(lcd, 1, left2);
	Lcd_int(lcd, data2);

	// end
}




bool DISPLAY_24H_TIME = true;


void display_default(Lcd_HandleTypeDef* lcd){
	// display everything + map

	// 1st row - date + time
	// lcd = 16
	// "MMM DD  " = 8
	// "HH:MM:SS" = 8

	// 2nd row - next alarm
	// "Alarm HH:MM" = 11
	//



	// --- output first row
	// output month
	Lcd_cursor(lcd, 0, 0);
	Lcd_string(lcd, M_STRING[CLOCK[MON]]);
	// output day
	Lcd_cursor(lcd, 0, 4);
	Lcd_int(lcd, CLOCK[DAY]);

	// find align right position
	int aleft = get_display_pos(A_RIGHT, 7);


	// output hours
	Lcd_cursor(lcd, 0, aleft);
	Lcd_int(lcd, (DISPLAY_24H_TIME ? CLOCK[HRR] : (CLOCK[HRR] % 12 == 0 ? 12 : CLOCK[HRR] % 12)));
	// output center thing
	Lcd_cursor(lcd, 0, aleft + 2);
	Lcd_string(lcd, ":");
	// output minutes
	Lcd_cursor(lcd, 0, aleft + 3);
	Lcd_int(lcd, CLOCK[MIN]);
	// output center thing
	Lcd_cursor(lcd, 0, aleft + 5);
	Lcd_string(lcd, ":");
	// output seconds
	if(CLOCK[SEC] < 10){
		Lcd_cursor(lcd, 0, aleft + 6);
		Lcd_int(lcd, 0);
		Lcd_cursor(lcd, 0, aleft + 7);
		Lcd_int(lcd, CLOCK[SEC]);
	}else{
		Lcd_cursor(lcd, 0, aleft + 6);
		Lcd_int(lcd, CLOCK[SEC]);
	}

	// --- output the second row
	// TODO - alarm stuff
	// intro string
	Lcd_cursor(lcd, 1, 0);
	Lcd_string(lcd, "ALARM ");

	if(HAS_TIMER){
		// print out hours
		aleft = get_display_pos(A_RIGHT, 4);
		if(ALARM[HRR] < 10){
			Lcd_cursor(lcd, 1, aleft);
			Lcd_int(lcd, 0);
			Lcd_cursor(lcd, 1, aleft + 1);
			Lcd_int(lcd, ALARM[HRR]);
		}else{
			Lcd_cursor(lcd, 1, aleft);
			Lcd_int(lcd, ALARM[HRR]);
		}
		Lcd_cursor(lcd, 1, aleft+2);
		Lcd_string(lcd, ":");


		if(ALARM[MIN] < 10){
			Lcd_cursor(lcd, 1, aleft + 3);
			Lcd_int(lcd, 0);
			Lcd_cursor(lcd, 1, aleft + 4);
			Lcd_int(lcd, ALARM[MIN]);
		}else{
			Lcd_cursor(lcd, 1, aleft + 3);
			Lcd_int(lcd, ALARM[MIN]);
		}
//		if(ALARM[SEC] < 10){
//			Lcd_cursor(lcd, 1, aleft + 3);
//			Lcd_int(lcd, 0);
//			Lcd_cursor(lcd, 1, aleft + 4);
//			Lcd_int(lcd, ALARM[SEC]);
//		}else{
//			Lcd_cursor(lcd, 1, aleft + 3);
//			Lcd_int(lcd, ALARM[SEC]);
//		}
	}else{
		aleft = get_display_pos(A_RIGHT, 6);
		Lcd_cursor(lcd, 1, aleft);
		Lcd_string(lcd, "NOT SET");
	}
}

void display_pomo(Lcd_HandleTypeDef* lcd, int* pc){

}



int t1_passed_t2(int* a, int* b){
	if (a[YRR] > b[YRR]) return true;
	if (a[MON] > b[MON]) return true;
	if (a[DAY] > b[DAY]) return true;
	if (a[HRR] > b[HRR]) return true;
	if (a[MIN] > b[MIN]) return true;
	if (a[SEC] > b[SEC]) return true;
	return false;
}

int get_display_pos(uint align, uint length){
	if (align == A_LEFT){
		return 0;
	} else if(align == A_RIGHT){
		return 16 - length - 1;
	}
	return 7 - (length / 2);
}

int get_int_length(int num){
	if (num < 0){
		return 0;
	}
	int i = 1;
	int c = 0;
	while(i <= num){
		i *= 10;
		c ++;
	}
	return c;
}




#endif /* INC_POMO_H_ */
