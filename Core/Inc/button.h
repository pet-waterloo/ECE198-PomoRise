/*
 * button.h
 *
 *  Created on: Nov 20, 2023
 *      Author: petthepotat
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "gpio.h"
#include "const.h"


bool BUTTONS[4] = {0, 0, 0, 0};
int HOLD_TIME[4] = {0, 0, 0, 0};

GPIO_TypeDef* B_mID[4] = {GPIOA, GPIOB, GPIOB, GPIOA};

uint16_t B_nID[4] = {GPIO_PIN_10, GPIO_PIN_3, GPIO_PIN_10, GPIO_PIN_8};


/*
 *  B1 = PA10 		 = pomo
 *  B2 = PB3 		 = timer (change)
 *  B3 = PB10		 = up
 *  B4 = PA8		 = down
 */


void update_buttons(){
	// update all buttons
	for(int i = 0; i < 4; i++){
		if(HAL_GPIO_ReadPin(B_mID[i], B_nID[i]) == GPIO_PIN_RESET){
			HOLD_TIME[i] = 0;
			BUTTONS[i] = false;
		}else{
			HOLD_TIME[i] += TEMP_DELTA_TIME;
			BUTTONS[i] = true;
		}
	}
}



#endif /* INC_BUTTON_H_ */
