/*
 * Alarm.h
 *
 *  Created on: Nov 20, 2023
 *      Author: petthepotat
 */

#ifndef INC_ALARM_H_
#define INC_ALARM_H_

#include <Time.hpp>


class Alarm {
private:
	Time tracker;

	int min;
	int hour;

public:
	Alarm(int min, int hour);
	virtual ~Alarm();
};



#endif /* INC_ALARM_H_ */
