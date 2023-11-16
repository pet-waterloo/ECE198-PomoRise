/*
 * pomo.h
 *
 *  Created on: Nov 16, 2023
 *      Author: petthepotat
 */

#ifndef INC_POMO_H_
#define INC_POMO_H_

#ifndef uint
#define uint unsigned int
#endif

#include "stdbool.h"



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


const uint CLOCK_SIZE = 6;

// -----
void second_update_clock(int*);
void display_info_s(Lcd_HandleTypeDef*, uint, char*, uint, uint, char*, uint);
void display_info_i(Lcd_HandleTypeDef*, uint, int, uint, int);
void display_clock(Lcd_HandleTypeDef*, int*);
bool ta_passed_tb(int*, int*);
int get_display_pos(uint, uint);
int get_int_length(int);

// -----
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

void display_clock(Lcd_HandleTypeDef* lcd, int* clock){
	// display everything + map

	// 1st row - date + time
	// lcd = 16
	// "MMM DD  " = 8
	// "   HH:MM" = 8

	// 2nd row - next alarm
	// "Alarm HH:MM" = 11
	//



	// --- output first row
	// output month
	Lcd_cursor(lcd, 0, 0);
	Lcd_string(lcd, M_STRING[clock[MON]]);
	// output day
	Lcd_cursor(lcd, 0, 4);
	Lcd_int(lcd, clock[DAY]);

	// find align right position
	int aleft = get_display_pos(A_RIGHT, 5);

	// output hours
	Lcd_cursor(lcd, 0, aleft);
	Lcd_int(lcd, clock[HRR]);
	// output center thing
	Lcd_cursor(lcd, 0, aleft + 2);
	Lcd_string(lcd, ":");
	// output minutes
	Lcd_cursor(lcd, 0, aleft + 3);
	Lcd_int(lcd, clock[MIN]);

	// --- output the second row
	// TODO - alarm stuff


}

bool ta_passed_tb(int* a, int* b){
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
