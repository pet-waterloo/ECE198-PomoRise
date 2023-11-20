/*
 * button.h
 *
 *  Created on: Nov 20, 2023
 *      Author: petthepotat
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "gpio.h"


bool BUTTONS[4] = {0, 0, 0, 0};

/*
 *  B1 = PA10
 *  B2 = PB3
 *  B3 = PB10
 *  B4 = PA8
 */


void update_buttons(){
	// button 1
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_RESET){
		BUTTONS[0] = false;
	}else{
		BUTTONS[0] = true;
	}
	// button 2
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET){
		BUTTONS[1] = false;
	}else{
		BUTTONS[1] = true;
	}
	// button 3
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_RESET){
		BUTTONS[2] = false;
	}else{
		BUTTONS[2] = true;
	}
	// button 4
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET){
		BUTTONS[3] = false;
	}else{
		BUTTONS[3] = true;
	}
}





#endif /* INC_BUTTON_H_ */
