/*
 * Speaker.h
 *
 *  Created on: Nov 20, 2023
 *      Author: petthepotat
 */

#ifndef INC_SPEAKER_H_
#define INC_SPEAKER_H_

#include "tim.h"


const int HERTZ = 500;

class Speaker {
private:
	TIM_HandleTypeDef hw;
	bool active;

public:
	Speaker(TIM_HandleTypeDef hw);
	virtual ~Speaker();

	void toggle();
	void set_state(bool);
	bool is_active();
	TIM_HandleTypeDef *get_device();
};

#endif /* INC_SPEAKER_H_ */
