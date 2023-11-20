/*
 * lcdwrap.cpp
 *
 *  Created on: Nov 19, 2023
 *      Author: petthepotat
 */


#include <lcdwrap.h>



LCD::LCD(LCD_HandleTypeDef* l): lcd(l){
	Lcd_clear(this->lcd);
}

LCD::~LCD(){

}

void LCD::_cursor(int row, int col){
	Lcd_cursor(this->lcd, row, col);
}

void LCD::_string(const char* string){
	for(uint8_t i = 0; i  < strlen(string); i++){
		lcd_write_data(this->lcd, string[i]);
	}
}

void LCD::_int(int num){
	Lcd_int(this->lcd, num);
}

void LCD::_double(double num, int dec){
	char buffer[16];
	sprintf(buffer, "%d", num);

	for(int i = 0; i < strlen(buffer); i++){
		if (buffer[i] == '.') break;
		lcd_write_data(this->lcd, buffer[i]);
	}

}

void LCD::_float(float num, int dec){
	char buffer[16];
	sprintf(buffer, "%f", num);

	for(int i = 0; i < strlen(buffer); i++){
		if (buffer[i] == '.') break;
		lcd_write_data(this->lcd, buffer[i]);
	}
}

