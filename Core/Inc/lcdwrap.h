/*
 * lcdwrap.h
 *
 *  Created on: Nov 19, 2023
 *      Author: petthepotat
 */

#ifndef INC_LCDWRAP_H_
#define INC_LCDWRAP_H_

#include "lcd.h"


/************************************** Wrapper Class **************************************/
class LCD {
private:
	Lcd_HandleTypeDef *lcd;


public:
	LCD(Lcd_HandleTypeDef *lcd);
	~LCD();

	void _cursor(int row, int col);
	void _string(const char* string);
	void _string(char* string);
	void _double(double num, int dec);
	void _float(float num, int dec);
	void _int(int num);
	void clear();

};





#endif /* INC_LCDWRAP_H_ */
