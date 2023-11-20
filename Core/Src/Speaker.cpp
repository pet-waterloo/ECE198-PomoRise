/*
 * Speaker.cpp
 *
 *  Created on: Nov 20, 2023
 *      Author: petthepotat
 */

#include <Speaker.h>

Speaker::Speaker(TIM_HandleTypeDef hw) {
	// TODO Auto-generated constructor stub
	active = false;
	this->hw = hw;
	this->set_state(false);
}

Speaker::~Speaker() {
	// TODO Auto-generated destructor stub
}

void Speaker::toggle(){
	active = !active;
	this->set_state(active);
}

void Speaker::set_state(bool state){
	if(!state){
		this->hw.Instance->CCR1 = HERTZ;
	}else{
		this->hw.Instance->CCR1 = 0;
	}
}

bool Speaker::is_active(){
	return this->active;
}

TIM_HandleTypeDef *Speaker::get_device(){
	return &this->hw;
}


